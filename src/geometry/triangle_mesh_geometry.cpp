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

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & dir = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		/// TODO
		const float EPSILON = 0.0000001;
		Vec3f		edge1, edge2, pvec, tvec, qvec;
		float		u, v, det, invDet;
		edge1 = v1 - v0;
		edge2 = v2 - v0;
		pvec  = cross( dir, edge2 );
		det	  = dot( edge1, pvec );

		if ( det > -EPSILON && det < EPSILON ) return false; // This ray is parallel to this triangle.

		invDet = 1.0 / det;

		tvec = o - v0;

		u = dot( tvec, pvec ) * invDet;
		if ( u < 0.0 || u > 1.0f ) return false;

		qvec = cross( tvec, edge1 );

		v = dot( dir, qvec ) * invDet;
		if ( v < 0.0 || u + v > 1.0f ) return false;


		// At this stage we can compute t to find out where the intersection point is on the line.
		p_t = dot( edge2, qvec ) * invDet;

		_faceNormal = ( 1 - u - v ) * _refMesh->_normals[ _v0 ] + u * _refMesh->_normals[ _v1 ]  + v * _refMesh->_normals[ _v2 ];

		return true;
	}

} // namespace RT_ISICG
