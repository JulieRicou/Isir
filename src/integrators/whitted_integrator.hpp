#ifndef __RT_ISICG_WHITTED_INTEGRATOR__
#define __RT_ISICG_WHITTED_INTEGRATOR__

#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public DirectLightingIntegrator
	{
	  public:
		WhittedIntegrator() : DirectLightingIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::WHITTED; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		Vec3f _LiRec( const Scene & p_scene,
					   const Ray &		 p_ray,
					   const float		 p_tMin,
					   const float		 p_tMax,
					   int			 p_nbBounces = 0,
					   float		 p_ior		 = 1,
					   std::string	 _lastObjectName = "" ) const;
		int	  _nbBounces = 10;

		std::string _lastObjectName = "";
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_DIRECT_LIGHTING_INTEGRATOR__
