#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/phong_brdf.hpp"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_specular, const int p_s )
			: BaseMaterial( p_name ), _phongBRDF( p_diffuse, p_specular ), _lambertBRDF( p_diffuse ), _s( p_s )
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _lambertBRDF.evaluate() * 0.7f
				   + _phongBRDF.evaluate( p_lightSample._direction, p_ray.getDirection(), p_hitRecord._normal, _s ) * 0.3f;
		}

		inline const Vec3f & getFlatColor() const override { return _lambertBRDF.getKd(); }

	  protected:
		PhongBRDF _phongBRDF;
		LambertBRDF _lambertBRDF;
		int			_s;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__
