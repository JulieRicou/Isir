#include "implicit_mandelbulb.hpp"

namespace RT_ISICG
{
	float ImplicitMandelbulb::_sdf( const Vec3f & p_point, const bool displace ) const
	{
		Vec3f w = p_point;
		float m	 = glm::dot( w, w );
		float x, x2, x4, y, y2, y4, z, z2, z4;
		float m2, m4;
		float dz = 1.0f;

		float k1, k2, k3, k4;

		for ( int i = 0; i < 4; i++ )
		{
			m2	= m * m;
			m4	= m2 * m2;
			dz	= 8.0 * sqrt( m4 * m2 * m ) * dz + 1.0;

			x	 = w.x;
			x2 = x * x;
			x4 = x2 * x2;
			y	 = w.y;
			y2 = y * y;
			y4 = y2 * y2;
			z	 = w.z;
			z2 = z * z;
			z4 = z2 * z2;

			k3 = x2 + z2;
			k2 = 1.0f / sqrt( k3 * k3 * k3 * k3 * k3 * k3 * k3 );
			k1 = x4 + y4 + z4 - 6.0f * y2 * z2 - 6.0f * x2 * y2 + 2.0f * z2 * x2;
			k4 = x2 - y2 + z2;

			w.x = p_point.x + 64.0f * x * y * z * ( x2 - z2 ) * k4 * ( x4 - 6.0f * x2 * z2 + z4 ) * k1 * k2;
			w.y = p_point.y - 16.0f * y2 * k3 * k4 * k4 + k1 * k1;
			w.z = p_point.z - 8.0f * y * k4 * ( x4 * x4 - 28.0f * x4 * x2 * z2 + 70.0f * x4 * z4 - 28.0f * x2 * z2 * z4 + z4 * z4 ) * k1 * k2;

			m = glm::dot( w, w );
			
			if ( m > 256.0 ) break;
		}

		// distance estimation (through the Hubbard-Douady potential)
		return 0.25 * log( m ) * sqrt( m ) / dz;
	}
} // namespace RT_ISICG