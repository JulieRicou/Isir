#ifndef __RT_ISICG_IMPLICIT_ROUNDED_CYLINDER__
#define __RT_ISICG_IMPLICIT_ROUNDED_CYLINDER__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitRoundedCylinder : public ImplicitSurface
	{
	  public:
		ImplicitRoundedCylinder()		   = delete;
		virtual ~ImplicitRoundedCylinder() = default;

		ImplicitRoundedCylinder( const std::string & p_name,
								 const bool			 p_displaceBool,
								 const Vec3f &		 p_center,
								 const float		 p_radiusCylinder,
								 const float		 p_radiusRounded,
								 const float		 p_height )
			: ImplicitSurface( p_name, p_displaceBool ), _center( p_center ), _radiusCylinder( p_radiusCylinder ),
			  _radiusRounded( p_radiusRounded ), _height( p_height )
		{
		}

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point, const bool displace = false ) const override;

		const Vec3f _center	   = VEC3F_ZERO;
		const float _radiusCylinder	   = 1.f;
		const float _radiusRounded = 0.2f;
		const float _height = 0.01f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_ROUNDED_CYLINDER__
