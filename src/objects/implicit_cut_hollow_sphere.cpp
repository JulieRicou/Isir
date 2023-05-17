#include "implicit_cut_hollow_sphere.hpp"

namespace RT_ISICG
{
	float ImplicitCutHollowSphere::_sdf( const Vec3f & p_point, const bool displace ) const 
	{
		if ( displace ) return _displace( p_point );
		// sampling independent computations (only depend on shape)
		float w = sqrt( _radius * _radius - _planePos * _planePos );

		// sampling dependant computations
		Vec2f q = Vec2f( length( Vec2f( p_point.x - _center.x, p_point.z - _center.z ) ), p_point.y - _center.y );
		return ( ( _planePos * q.x < w * q.y ) ? length( q - Vec2f( w, _planePos ) ) : abs( length( q ) - _radius ) ) - _thickness;
	}
} // namespace RT_ISICG
