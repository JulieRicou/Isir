#include "triangle_mesh.hpp"

namespace RT_ISICG
{
	bool MeshTriangle::intersect( const Ray & p_ray,
								  const float p_tMin,
								  const float p_tMax,
								  HitRecord & p_hitRecord ) const
	{
		if ( useBVH ) return _bvh.intersect( p_ray, p_tMin, p_tMax, p_hitRecord );
		else if (useAABB)
		{
			if ( _aabb.intersect( p_ray, p_tMin, p_tMax ) )
			{
				float  tClosest = p_tMax;			 // Hit distance.
				size_t hitTri	= _triangles.size(); // Hit triangle id.
				for ( size_t i = 0; i < _triangles.size(); i++ )
				{
					float t;
					if ( _triangles[ i ].intersect( p_ray, t ) )
					{
						if ( t >= p_tMin && t <= tClosest )
						{
							tClosest = t;
							hitTri	 = i;
						}
					}
				}
				if ( hitTri != _triangles.size() ) // Intersection found.
				{
					p_hitRecord._point	= p_ray.pointAtT( tClosest );
					p_hitRecord._normal = _triangles[ hitTri ].getFaceNormal();
					p_hitRecord.faceNormal( p_ray.getDirection() );
					p_hitRecord._distance = tClosest;
					p_hitRecord._object	  = this;

					return true;
				}
			}
			return false;
		}
		else
		{
			float  tClosest = p_tMax;			 // Hit distance.
			size_t hitTri	= _triangles.size(); // Hit triangle id.
			for ( size_t i = 0; i < _triangles.size(); i++ )
			{
				float t;
				if ( _triangles[ i ].intersect( p_ray, t ) )
				{
					if ( t >= p_tMin && t <= tClosest )
					{
						tClosest = t;
						hitTri	 = i;
					}
				}
			}
			if ( hitTri != _triangles.size() ) // Intersection found.
			{
				p_hitRecord._point	= p_ray.pointAtT( tClosest );
				p_hitRecord._normal = _triangles[ hitTri ].getFaceNormal();
				p_hitRecord.faceNormal( p_ray.getDirection() );
				p_hitRecord._distance = tClosest;
				p_hitRecord._object	  = this;

				return true;
			}
			return false;
		}
	}

	bool MeshTriangle::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		if ( useBVH ) return _bvh.intersectAny( p_ray, p_tMin, p_tMax );
		else if ( useAABB ) {
			if ( _aabb.intersect( p_ray, p_tMin, p_tMax ) ) {
				for ( size_t i = 0; i < _triangles.size(); i++ )
				{
					float t;
					if ( _triangles[ i ].intersect( p_ray, t ) )
					{
						if ( t >= p_tMin && t <= p_tMax ) return true; // No need to search for the nearest.
					}
				}
				return false;
			}
		}
		else
		{
			for ( size_t i = 0; i < _triangles.size(); i++ )
			{
				float t;
				if ( _triangles[ i ].intersect( p_ray, t ) )
				{
					if ( t >= p_tMin && t <= p_tMax ) return true; // No need to search for the nearest.
				}
			}
			return false;
		}

	}
} // namespace RT_ISICG
