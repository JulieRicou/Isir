#ifndef __RT_ISICG_IMPLICIT_LINK__
#define __RT_ISICG_IMPLICIT_LINK__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitLink : public ImplicitSurface
	{
	  public:
		ImplicitLink()					   = delete;
		virtual ~ImplicitLink() = default;

		ImplicitLink( const std::string & p_name, const bool p_displaceBool,
								 const Vec3f &		 p_center,
								 const float		 p_width,
								 const float		 p_thickness,
								 const float		 p_height )
			: ImplicitSurface( p_name, p_displaceBool ), _center( p_center ), _width( p_width ), _thickness( p_thickness ),
			  _height( p_height )
		{
		}

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point, const bool displace = false ) const override;

		const Vec3f _center	   = VEC3F_ZERO;
		const float _width   = 1.f;
		const float _thickness   = 1.f;
		const float _height	   = 0.2f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_LINK__
