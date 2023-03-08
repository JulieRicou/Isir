#include "quad_light.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_point ) const
	{
		Vec3f position = _position + _u * randomFloat() + _v * randomFloat();

		float distance = glm::distance( position, p_point );

		Vec3f direction = glm::normalize(position - p_point);

		float pdf = 1.f / _area * ( pow( distance, 2 ) / dot( _n, direction ) );

		Vec3f radiance = (_color * _power) / pdf;

		return LightSample( direction, distance, radiance, pdf );
	}

} // namespace RT_ISICG