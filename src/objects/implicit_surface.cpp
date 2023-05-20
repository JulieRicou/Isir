#include "implicit_surface.hpp"

namespace RT_ISICG
{
	bool ImplicitSurface::intersect( const Ray & p_ray,
									 const float p_tMin,
									 const float p_tMax,
									 HitRecord & p_hitRecord ) const
	{
		/// TODO
		float t	  = 0;
		float d	  = 0;

		while ( t < p_tMax)
		{
			d = _sdf( p_ray.pointAtT( t ), _displaceBool );
			t += d;
			if ( d <= _minDistance ) 
			{
				p_hitRecord._point	= p_ray.pointAtT( t );
				p_hitRecord._normal = _evaluateNormal( p_ray.pointAtT( t ) );
				p_hitRecord.faceNormal( p_ray.getDirection() );
				p_hitRecord._distance = t;
				p_hitRecord._object	  = this;
				return true; 
			}
		}

		return false;
	}

	bool ImplicitSurface::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		Vec3f pos = p_ray.getOrigin();
		float t	  = 0;
		float d	  = 0;

		while ( t < p_tMax )
		{
			d = _sdf( p_ray.pointAtT( t ), _displaceBool );
			t +=  d;
			if ( d <= _minDistance) 
			{
				return true;
			}
		}

		return false;
	}

	float ImplicitSurface::_displace( const Vec3f & p_point ) const
	{
		float d1 = _sdf( p_point, false );
		float d2 = sin( 10.0f * p_point.x ) * sin( 10.0f * p_point.y ) * sin( 10.0f * p_point.z );
		return d1 + d2;
	}
} // namespace RT_ISICG
