#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) ) { 
			return _directLighting( p_scene, hitRecord );
		}
		else { return _backgroundColor; }
	}

	Vec3f DirectLightingIntegrator::_directLighting( const Scene & p_scene, const HitRecord & hitRecord) const {
		
		Vec3f Li = VEC3F_ZERO;

		for ( BaseLight * light : p_scene.getLights() ) 
		{
			LightSample sample = light->sample( hitRecord._point );
			float		cosT   = glm::max( dot( sample._direction, hitRecord._normal ), 0.f );
			//Li += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, sample ) * sample._radiance * cosT;
			Li += hitRecord._object->getMaterial()->getFlatColor() * cosT * sample._radiance; //			 
		}

		return Li;
	}

} // namespace RT_ISICG