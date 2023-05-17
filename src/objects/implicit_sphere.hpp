#ifndef __RT_ISICG_IMPLICIT_SPHERE__
#define __RT_ISICG_IMPLICIT_SPHERE__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitSphere : public ImplicitSurface
	{
	  public:
		ImplicitSphere()		   = delete;
		virtual ~ImplicitSphere() = default;

		ImplicitSphere( const std::string & p_name, const bool p_displaceBool, const Vec3f & p_center, const float p_radius ) : ImplicitSurface( p_name, p_displaceBool ), _center(p_center), _radius(p_radius) {}

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point, const bool displace = false ) const override;

		const Vec3f _center = VEC3F_ZERO;
		const float _radius = 1.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SPHERE__
