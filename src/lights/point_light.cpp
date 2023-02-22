#include "point_light.hpp"


namespace RT_ISICG
{
	LightSample PointLight::sample( const Vec3f & p_point ) const { 

		float distance = glm::distance( _position, p_point );

		Vec3f radiance = _color * _power;

		float attenuation =  1.f / glm::pow( distance, 2 );

		return LightSample( glm::normalize( _position - p_point ), distance, radiance * attenuation, 1.f );
	}

} // namespace RT_ISICG