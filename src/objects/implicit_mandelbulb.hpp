#ifndef __RT_ISICG_IMPLICIT_MANDELBULB__
#define __RT_ISICG_IMPLICIT_MANDELBULB__

#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitMandelbulb : public ImplicitSurface
	{
	  public:
		ImplicitMandelbulb()			   = delete;
		virtual ~ImplicitMandelbulb() = default;

		ImplicitMandelbulb( const std::string & p_name,
								 const bool			 p_displaceBool,
								 const Vec3f &		 p_center )
			: ImplicitSurface( p_name, p_displaceBool ), _center( p_center )
		{
		}

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point, const bool displace = false ) const override;

		const Vec3f _center			= VEC3F_ZERO;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_MANDELBULB__
