#ifndef __RT_ISICG_MATTE_MATERIAL__
#define __RT_ISICG_MATTE_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"

namespace RT_ISICG
{
	class MatteMaterial : public BaseMaterial
	{
	  public:
		MatteMaterial( const std::string & p_name, const Vec3f & p_diffuse, const float p_sigma )
			: BaseMaterial( p_name ), _brdf( p_diffuse ), _sigma(p_sigma)
		{
		}

		virtual ~MatteMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _brdf.evaluate( p_lightSample._direction, -p_ray.getDirection(), p_hitRecord._normal, _sigma );
		}

		inline const Vec3f & getFlatColor() const override { return _brdf.getKd(); }

	  protected:
		OrenNayarBRDF _brdf;
		float _sigma;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MATTE_MATERIAL__
