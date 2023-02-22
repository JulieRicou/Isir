#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		/// TODO ! _u ? _v ? _w ?
		_w = -glm::normalize( p_lookAt - p_position );
		_u = glm::normalize(glm::cross( p_up, _w ));
		_v = glm::normalize(glm::cross( _w, _u ));

		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?

		float h = (std::max(0.f,glm::tan( glm::radians(_fovy) / 2.f )) * _focalDistance) * 2.f;
		float w = h * _aspectRatio;

		_viewportTopLeftCorner = _position + (w / 2.f ) * -_u + ( h / 2.f ) * _v + _focalDistance * -_w;

		_viewportU = _u * w;
		_viewportV = -_v * h;
	}

} // namespace RT_ISICG
