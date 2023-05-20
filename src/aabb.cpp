#include "aabb.hpp"

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		float tmin, tmax, tymin, tymax, tzmin, tzmax;
		if ( p_ray.getDirection().x >= 0 )
		{
			tmin = ( _min.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
			tmax = ( _max.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
		}
		else
		{
			tmin = ( _max.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
			tmax = ( _min.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
		}
		if ( p_ray.getDirection().y >= 0 )
		{
			tymin = ( _min.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
			tymax = ( _max.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
		}
		else
		{
			tymin = ( _max.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
			tymax = ( _min.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
		}

		if ( ( tmin > tymax ) || ( tymin > tmax ) ) return false;
		if ( tymin > tmin ) tmin = tymin;
		if ( tymax < tmax ) tmax = tymax;
		if ( p_ray.getDirection().z >= 0 )
		{
			tzmin = ( _min.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
			tzmax = ( _max.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
		}
		else
		{
			tzmin = ( _max.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
			tzmax = ( _min.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
		}
		if ( ( tmin > tzmax ) || ( tzmin > tmax ) ) return false;
		if ( tzmin > tmin ) tmin = tzmin;
		if ( tzmax < tmax ) tmax = tzmax;
		return ( ( tmin < p_tMax ) && ( tmax > p_tMin ) );

	}
} // namespace RT_ISICG
