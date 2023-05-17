#ifndef __RT_ISICG_PHONG_BRDF__
#define __RT_ISICG_PHONG_BRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_kd, const Vec3f & p_ks ) : _kd( p_kd ), _ks( p_ks ) {};

		inline Vec3f evaluate( Vec3f dI, Vec3f dO, Vec3f n, const float s = 8 ) const
		{
			const Vec3f dR		  = glm::reflect( dI, n );
			const float cosThetaI = glm::max( glm::dot( n, dI ) , 0.f);
			const float cosThetaR = glm::max( glm::dot( -dO, dR ), 0.f );

			return _ks / cosThetaI * glm::pow( cosThetaR, s );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		Vec3f _ks = WHITE;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_PHONG_BRDF__