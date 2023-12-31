#ifndef __RT_ISICG_METALLIC_MATERIAL__
#define __RT_ISICG_METALLIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/cook_torrance_brdf.hpp"
#include "brdfs/oren_nayar_brdf.hpp"

namespace RT_ISICG
{
	class MetallicMaterial : public BaseMaterial
	{
	  public:
		MetallicMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_specular, const float & p_metalness, const float p_roughness )
			: BaseMaterial( p_name ), _cookTorranceBRDF( p_diffuse, p_specular ), _orenNayarBRDF( p_diffuse ),
			  _metalness( p_metalness ), _roughness( p_roughness ), _specular( p_specular )
		{
		}

		virtual ~MetallicMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			const Vec3f diffuse = _orenNayarBRDF.evaluate( p_lightSample._direction, -p_ray.getDirection(), p_hitRecord._normal );
			const Vec3f specular = _cookTorranceBRDF.evaluate( p_lightSample._direction, p_ray.getDirection(), p_hitRecord._normal, _specular, _roughness );
			return ( 1 - _metalness ) * diffuse + _metalness * specular;
		}

		inline const Vec3f & getFlatColor() const override { return _orenNayarBRDF.getKd(); }

	  protected:
		Vec3f			 _specular;
		CookTorranceBRDF _cookTorranceBRDF;
		OrenNayarBRDF _orenNayarBRDF;
		float			 _metalness = 0;
		float			 _roughness = 0;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_METALLIC_MATERIAL__
