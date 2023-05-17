#include "implicit_sphere.hpp"

namespace RT_ISICG
{
	float ImplicitSphere::_sdf( const Vec3f & p_point, const bool displace ) const
	{
		if ( displace ) return _displace( p_point );
		return length( p_point - _center ) - _radius;
	}
} // namespace RT_ISICG
