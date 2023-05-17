#ifndef __RT_ISICG_IMPLICIT_SURFACE__
#define __RT_ISICG_IMPLICIT_SURFACE__

#include "base_object.hpp"

namespace RT_ISICG
{
	class ImplicitSurface : public BaseObject
	{
	  public:
		ImplicitSurface()		   = delete;
		virtual ~ImplicitSurface() = default;

		ImplicitSurface( const std::string & p_name, const bool p_displaceBool ) : BaseObject( p_name ), _displaceBool(p_displaceBool) {}

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		virtual bool intersect( const Ray & p_ray,
								const float p_tMin,
								const float p_tMax,
								HitRecord & p_hitRecord ) const override;

		// Check for any intersection between p_tMin and p_tMax.
		virtual bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		float _displace( const Vec3f & p_point ) const;

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point, const bool displace ) const = 0;

		// Evaluate normal by computing gradient at 'p_point'
		virtual Vec3f _evaluateNormal( const Vec3f & p_point ) const
		{
			/// TODO
			Vec2f e = Vec2f( 1.0, -1.0 ) * 0.5773f * 0.0005f;
			Vec3f xyy = Vec3f( e.x, e.y, e.y );
			Vec3f yyx = Vec3f( e.y, e.y, e.x );
			Vec3f yxy = Vec3f( e.y, e.x, e.y );
			Vec3f xxx = Vec3f( e.x, e.x, e.x );
			return normalize( xyy * _sdf( p_point + xyy, _displaceBool ) + yyx * _sdf( p_point + yyx, _displaceBool )
							  + yxy * _sdf( p_point + yxy, _displaceBool )
							  + xxx * _sdf( p_point + xxx, _displaceBool ) );
		}

	  private:
		const float _minDistance = 1e-4f;
		const bool	_displaceBool = false;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
