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
		Vec3f LiTemp = VEC3F_ZERO;

		for ( BaseLight * light : p_scene.getLights() ) 
		{
			if (light->getIsSurface()) {
				for ( size_t i = 0; i < _nbLightSamples; i++ )
				{
					LightSample lSample	  = light->sample( hitRecord._point );
					Ray			shadowRay( hitRecord._point, lSample._direction );
					shadowRay.offset( hitRecord._normal );
					if ( !p_scene.intersectAny( shadowRay, 0.f, lSample._distance ) )
					{
						float cosT = glm::max( dot( lSample._direction, hitRecord._normal ), 0.f );
						LiTemp += hitRecord._object->getMaterial()->shade(shadowRay, hitRecord, lSample) * cosT * lSample._radiance;
					}
				}
				LiTemp /= _nbLightSamples;
				Li += LiTemp;
			}
			else
			{
				LightSample lSample	  = light->sample( hitRecord._point );
				Ray			shadowRay( hitRecord._point, lSample._direction );
				shadowRay.offset( hitRecord._normal );
				if ( !p_scene.intersectAny( shadowRay, 0.f, lSample._distance ) )
				{
					float cosT = glm::max( dot( lSample._direction, hitRecord._normal ), 0.f );
					Li += hitRecord._object->getMaterial()->shade( shadowRay, hitRecord, lSample ) * cosT * lSample._radiance;
				}	
			}
				 
		}

		return Li;
	}

} // namespace RT_ISICG
