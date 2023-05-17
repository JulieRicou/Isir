#ifndef __RT_ISICG_IMPLICIT_CUT_HOLLOW_SPHERE__
#define __RT_ISICG_IMPLICIT_CUT_HOLLOW_SPHERE__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitCutHollowSphere : public ImplicitSurface
	{
	  public:
		ImplicitCutHollowSphere() = delete;
		virtual ~ImplicitCutHollowSphere() = default;

		ImplicitCutHollowSphere( const std::string & p_name, const bool p_displaceBool, const Vec3f & p_center, const float p_radius, const float p_planePos, const float p_thickness )
			: ImplicitSurface( p_name, p_displaceBool ), _center( p_center ), _radius( p_radius ), _planePos( p_planePos ), _thickness(p_thickness)
		{
		}

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point, const bool displace = false ) const override;

		const Vec3f _center = VEC3F_ZERO;
		const float _radius = 1.f;
		const float _planePos = 0.2f;
		const float _thickness = 0.01f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_CUT_HOLLOW_SPHERE__
