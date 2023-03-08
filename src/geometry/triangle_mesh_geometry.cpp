#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		/// TODO
		const float EPSILON = 0.0000001;
		Vec3f		edge1, edge2, h, s, q;
		float		a, f, u, v;
		edge1 = v1 - v0;
		edge2 = v2 - v0;
		h	  = cross( d, edge2 );
		a	  = dot(edge1, h );
		if ( a > -EPSILON && a < EPSILON ) return false; // This ray is parallel to this triangle.
		f = 1.0 / a;
		s = o - v0;
		u = f * dot(s, h );
		if ( u < 0.0 || u > 1.0 ) return false;
		q = cross(s, edge1 );
		v = f * dot(d, q );
		if ( v < 0.0 || u + v > 1.0 ) return false;
		// At this stage we can compute t to find out where the intersection point is on the line.
		p_t = f * dot( edge2, q );
		if ( p_t > EPSILON ) // ray intersection
		{
			return true;
		}
		else // This means that there is a line intersection but not a ray intersection.
		return false;
	}

} // namespace RT_ISICG
