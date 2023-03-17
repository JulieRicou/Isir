#include "aabb.hpp"

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		Vec3f pos = p_ray.getOrigin();
		while (abs(glm::distance( pos, p_ray.getOrigin())) < p_tMax) {
			pos += p_ray.getDirection();
			if ( _min.x < pos.x && _min.y < pos.y && _min.z < pos.z && _max.x > pos.x && _max.y > pos.y && _max.z > pos.z )
			{
				return true;
			}
		}
		return false;
	}
} // namespace RT_ISICG
