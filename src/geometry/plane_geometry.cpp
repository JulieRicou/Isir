#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t1 ) const
	{
		/// TODO !
		p_t1 = -1.f;

		// On suppose les vecteurs normalises
		float den = dot( _normal, p_ray.getDirection() );
		// Si le plan et le rayon ne sont pas parall�les
		if ( den != 0 )
		{ // Attention � la comparaison avec 0
			Vec3f po = _point - p_ray.getOrigin();
			p_t1	 = dot( po, _normal ) / den;
			return p_t1;
		}
		// Sinon, pas d�intersection
		return false;
	}

} // namespace RT_ISICG