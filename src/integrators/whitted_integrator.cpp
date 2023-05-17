#include "whitted_integrator.hpp"
#include "direct_lighting_integrator.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
										const float	  p_tMax ) const
	{
		return _LiRec( p_scene, p_ray, p_tMin, p_tMax );
	}

	Vec3f WhittedIntegrator::_LiRec( const Scene & p_scene,
									  const Ray &		p_ray,
									  const float		p_tMin,
									  const float		p_tMax,
									  int				p_nbBounces,
									  float p_ior,
									  std::string	_lastObjectName ) const
	{
		if ( p_nbBounces > _nbBounces ) { return BLACK; }
		Vec3f	  Li = VEC3F_ZERO;
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			if ( hitRecord._object->getMaterial()->isMirror() )
			{
				Ray reflectedRay( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
				reflectedRay.offset( hitRecord._normal);
				p_nbBounces++;
				Li = _LiRec( p_scene, reflectedRay, p_tMin, p_tMax, p_nbBounces, p_ior, hitRecord._object->getName() );
			}
			else if ( hitRecord._object->getMaterial()->isTransparent() )
			{
				float n1 = p_ior;
				float n2 = 1;
				if ( _lastObjectName == "" || _lastObjectName != hitRecord._object->getName() )
				{
					n2 = hitRecord._object->getMaterial()->getIOR();
				}

				const float cosThetaI = glm::max( glm::dot( -p_ray.getDirection(), hitRecord._normal ), 0.0f );
				const float thetaI = glm::acos( cosThetaI );

				const float squaredOneMinus = glm::sqrt( 1.0f - glm::pow( ( n1 / n2 ) * glm::sin( thetaI ), 2.0f ) );

				float Rs = glm::pow( ( n1 * cosThetaI - n2 * squaredOneMinus) / ( n1 * cosThetaI + n2 * squaredOneMinus ), 2.0f );
				float Rp = glm::pow( ( n1 * squaredOneMinus - n2 * cosThetaI ) / ( n1 * squaredOneMinus + n2 * cosThetaI ), 2.0f) ;

				float kr = 0.5f * ( Rs + Rp );
				p_nbBounces++;
				Ray reflectedRay( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
				reflectedRay.offset( hitRecord._normal );
				Li += _LiRec( p_scene, reflectedRay, 0.0f, p_tMax, p_nbBounces, n1, hitRecord._object->getName() ) * kr;

				if ( kr < 1 )
				{
					Ray refractedRay( hitRecord._point,
									  glm::refract( p_ray.getDirection(), hitRecord._normal, n1 / n2 ) );
					refractedRay.offset( -hitRecord._normal );
					Li += _LiRec( p_scene, refractedRay, 0.0f, p_tMax, p_nbBounces, n2, hitRecord._object->getName() ) * ( 1.0f - kr );
				}
			}
			else { Li = _directLighting( p_scene, hitRecord ); }

			return Li;
		}
		else { return _backgroundColor; }
	}

} // namespace RT_ISICG
