#include "implicit_rounded_cylinder.hpp"

namespace RT_ISICG
{
	float ImplicitRoundedCylinder::_sdf( const Vec3f & p_point, const bool displace ) const
	{ 
		if ( displace ) return _displace( p_point );
		Vec2f d = Vec2f( length( Vec2f( p_point.x - _center.x, p_point.z - _center.z ) ) - 2.0 * _radiusCylinder + _radiusRounded, abs( p_point.y - _center.y ) - _height );
		return std::min( std::max( d.x, d.y ), 0.f ) + length( max( d, 0.f ) ) - _radiusRounded;
	}
} // namespace RT_ISICG