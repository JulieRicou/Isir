#ifndef __RT_ISICG_COOK_TORRANCE_BRDF__
#define __RT_ISICG_COOK_TORRANCE_BRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_kd, const Vec3f & p_ks ) : _kd( p_kd ), _ks( p_ks ) {};

		inline Vec3f evaluate( Vec3f dI, Vec3f dO, Vec3f n, Vec3f F0, float roughness = 0.3f ) const
		{
			const float squaredAlpha = glm::pow( roughness, 4 );
			const Vec3f	h	  = glm::normalize(dO + dI);

			const float D = squaredAlpha / ( PIf * glm::pow( glm::pow( glm::dot( n, h ), 2 ) * (squaredAlpha - 1) + 1, 2 ) );
			const float G = G1( glm::dot( n, dO ), roughness ) * G1( glm::dot( n, dI ), roughness );
			const Vec3f F = F0 + ( Vec3f( 1 ) - F0 ) * glm::pow( Vec3f( 1 ) - glm::dot( h, dO ), Vec3f( 5 ) );

			const Vec3f frs = ( D * F * G ) / ( 4 * glm::dot( dO, n ) * glm::dot( dI, n ) );

			return frs;
		}

		inline float G1( float x, float roughness ) const
		{ 
			const float k = glm::pow( roughness + 1, 2 ) / 8;
			return x / ( x * ( 1 - k ) + k );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		Vec3f _ks = WHITE;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_COOK_TORRANCE_BRDF__