#include "implicit_link.hpp"

namespace RT_ISICG
{
	float ImplicitLink::_sdf( const Vec3f & p_point, const bool displace ) const
	{
		if ( displace ) return _displace( p_point );
		Vec3f q = Vec3f( p_point.x - _center.x, std::max( abs( p_point.y - _center.y ) - _height, 0.f ), p_point.z - _center.z );
		return length( Vec2f( length( Vec2f( q.x, q.y ) ) - _width, q.z ) ) - _thickness;
	}
} // namespace RT_ISICG
