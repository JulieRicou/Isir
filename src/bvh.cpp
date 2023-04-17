#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"
#include <algorithm>

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;

		Chrono chr;
		chr.start();

		/// TODO
		_root = new BVHNode();
		_root->_firstTriangleId = 0;
		_root->_lastTriangleId = _triangles->size();

		_buildRec( _root, 0, _triangles->size(), 0 );

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		/// TODO
		if ( _root->_aabb.intersect( p_ray, p_tMin, p_tMax ) ) 
		{ 
			return _intersectRec(_root, p_ray, p_tMin, p_tMax, p_hitRecord);
		}
		else return false;
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		if ( _root->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
		{
			return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax );
		}
		else return false;
	}

	void BVH::_buildRec( BVHNode *			p_node,
						 const unsigned int p_firstTriangleId,
						 const unsigned int p_lastTriangleId,
						 const unsigned int p_depth )
	{
		p_node->_firstTriangleId = p_firstTriangleId;
		p_node->_lastTriangleId	 = p_lastTriangleId;

		p_node->_aabb = AABB();
		for ( unsigned id = p_firstTriangleId; id < p_lastTriangleId; id++ )
		{
			p_node->_aabb.extend( (*_triangles)[ id ].getAABB());
		}

		// Check if we reached the maximum depth or if the number of triangles in the node is below the minimum
		// threshold
		if ( p_depth < _maxDepth && (p_lastTriangleId - p_firstTriangleId) > _maxTrianglesPerLeaf )
		{
			// Find the axis with the maximum length of the AABB
			int axis = p_node->_aabb.largestAxis();

			// Calculate the midpoint of the AABB along the selected axis
			float mid = p_node->_aabb.centroid()[ axis ];

			std::vector<TriangleMeshGeometry> * _tri = _triangles;

			// Partition the triangle IDs based on the midpoint
			std::vector<TriangleMeshGeometry>::iterator ite = std::partition(
				_triangles->begin() + p_firstTriangleId,
				_triangles->begin() + p_lastTriangleId,
				[ = ]( TriangleMeshGeometry & triangle ) { return triangle.getAABB().centroid()[ axis ] < mid; } );

			int splitIndex = std::distance( _triangles->begin(), ite );

			// Create child nodes and build them recursively
			p_node->_left  = new BVHNode();
			p_node->_right = new BVHNode();
			_buildRec( p_node->_left, p_firstTriangleId, splitIndex, p_depth + 1 );
			_buildRec( p_node->_right, splitIndex, p_lastTriangleId, p_depth + 1 );
		}
	}
	

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		/// TODO
		if ( p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
		{
			if ( !p_node->isLeaf() )
			{
				bool left = _intersectRec( p_node->_left, p_ray, p_tMin, p_tMax, p_hitRecord );
				bool right = _intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, p_hitRecord );
				return ( left || right );
			}
			else
			{
				float  tClosest = p_tMax; // Hit distance.
				size_t hitTri	= NULL;	  // Hit triangle id.
				for ( size_t i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ )
				{
					float t;
					if ( (*_triangles)[ i ].intersect( p_ray, t ) )
					{
						if ( t >= p_tMin && t <= tClosest )
						{
							tClosest = t;
							hitTri	 = i;
						}
					}
				}
				if ( hitTri != NULL && p_hitRecord._distance > tClosest ) // Intersection found.
				{
					p_hitRecord._point	= p_ray.pointAtT( tClosest );
					p_hitRecord._normal = (*_triangles)[ hitTri ].getFaceNormal();
					p_hitRecord.faceNormal( p_ray.getDirection() );
					p_hitRecord._distance = tClosest;
					p_hitRecord._object	  = (*_triangles)[ hitTri ].getRefMesh();

					return true;
				}
			}
		}
		return false;

	}
	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		/// TODO
		if ( p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
		{
			if ( !p_node->isLeaf() )
			{
				return (_intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax )
					   || _intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax ));
			}
			else
			{
				for ( size_t i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ )
				{
					float t;
					if ( (*_triangles)[ i ].intersect( p_ray, t ) )
					{
						if ( t >= p_tMin && t <= p_tMax ) return true; // No need to search for the nearest.
					}
				}
			}
		}
		return false;
	}
} // namespace RT_ISICG
