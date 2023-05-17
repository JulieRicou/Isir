#ifndef __RT_ISICG_OREN_NAYAR_BRDF__
#define __RT_ISICG_OREN_NAYAR_BRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd ) : _kd( p_kd ) {};

		inline Vec3f evaluate( Vec3f dI, Vec3f dO, Vec3f n, float sigma = 0.6f ) const	
		{
			const Vec3f normalizedNormal = glm::normalize( n );

			const float cosThetaI = glm::max( glm::dot( normalizedNormal, dI ), 0.0f );
			const float cosThetaO = glm::max( glm::dot( normalizedNormal, dO ), 0.0f );

			const float thetaI	= glm::acos( cosThetaI );
			const float thetaO	= glm::acos( cosThetaO );

			const float phiI   = glm::atan( glm::sqrt( glm::pow( dI.x, 2 ) + glm::pow( dI.y, 2 ) ) / dI.z );
			const float phiO   = glm::atan( glm::sqrt( glm::pow( dO.x, 2 ) + glm::pow( dO.y, 2 ) ) / dO.z );

			const float squaredSigma = glm::pow( sigma, 2 );

			const float a = 1.f - 0.5f * ( squaredSigma / ( squaredSigma + 0.33f ) );
			const float b = 0.45f * ( squaredSigma / ( squaredSigma + 0.09f ) );
			
			const float alpha = glm::max( thetaI, thetaO );
			const float beta   = glm::min( thetaI, thetaO );

			const float gamma = glm::max( 0.f, glm::cos( phiI - phiO ) );

			return _kd / PIf * ( a + ( b * gamma * glm::sin( alpha ) * glm::tan( beta ) ) );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_OREN_NAYAR_BRDF__