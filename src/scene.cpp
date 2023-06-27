#include "scene.hpp"
#include "materials/color_material.hpp"
#include "materials/lambert_material.hpp"
#include "materials/matte_material.hpp"
#include "materials/plastic_material.hpp"
#include "materials/metallic_material.hpp"
#include "materials/mirror_material.hpp"
#include "materials/transparent_material.hpp"
#include "objects/sphere.hpp"
#include "objects/plane.hpp"
#include "objects/triangle_mesh.hpp"
#include "objects/implicit_sphere.hpp"
#include "objects/implicit_cut_hollow_sphere.hpp"
#include "objects/implicit_link.hpp"
#include "objects/implicit_rounded_cylinder.hpp"
#include "objects/implicit_mandelbulb.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace RT_ISICG
{
	Scene::Scene() { _addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			delete object.second;
		}
		for ( const MaterialMapPair & material : _materialMap )
		{
			delete material.second;
		}
		for ( const BaseLight * light : _lightList )
		{
			delete light;
		}
	}

	void Scene::init( int tpToInit, int sceneToInit )
	{

		switch ( tpToInit )
		{
		//********TP1********
		case 1:
			// Add objects.
			_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

			// Add materials.
			_addMaterial( new ColorMaterial( "Blue", BLUE ) );

			// Link objects and materials.
			_attachMaterialToObject( "Blue", "Sphere1" );
			break;


		//********TP2********
		case 2:
			// Add objects.
			_addObject( new Plane( "Plane1", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );

			// Add materials.
			_addMaterial( new ColorMaterial( "Red", RED ) );

			// Link objects and materials.
			_attachMaterialToObject( "Red", "Plane1" );

			//Add light
			_addLight( new PointLight( Vec3f( 1.f, 10.f, 1.f ), WHITE, 100.f ) );
	
			// Add objects.
			_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

			// Add materials.
			_addMaterial( new ColorMaterial( "Blue", BLUE ) );

			// Link objects and materials.
			_attachMaterialToObject( "Blue", "Sphere1" );
			break;

			
		//********TP3********
		case 3:
			// Add objects.
			_addObject( new Plane( "Plane1", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );

			// Add materials.
			_addMaterial( new ColorMaterial( "Red", RED ) );

			// Link objects and materials.
			_attachMaterialToObject( "Red", "Plane1" );

			// Add light
			_addLight( new QuadLight( Vec3f( 1.f, 10.f, 2.f ), Vec3f( -2, 0, 0 ), Vec3f( 0, 0, 2 ), WHITE, 40.f ) );

			// Add objects.
			_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

			// Add materials.
			_addMaterial( new ColorMaterial( "Blue", BLUE ) );

			// Link objects and materials.
			_attachMaterialToObject( "Blue", "Sphere1" );
			break;


		//********TP4********
		case 4:
			// ================================================================
			// Add materials .
			// ================================================================
			_addMaterial( new ColorMaterial( "RedColor", RED ) );
			_addMaterial( new ColorMaterial( "GreenColor", GREEN ) );
			_addMaterial( new ColorMaterial( "BlueColor", BLUE ) );
			_addMaterial( new ColorMaterial( "GreyColor", GREY ) );
			_addMaterial( new ColorMaterial( "MagentaColor", MAGENTA ) );
			_addMaterial( new ColorMaterial( "YellowColor", YELLOW ) );
			_addMaterial( new ColorMaterial( "CyanColor", CYAN ) );

			// ================================================================
			// Add objects .
			// ================================================================
			// OBJ.
			switch ( sceneToInit )
			{
			//UVSphere
			case 1:
				loadFileTriangleMesh( "UVsphere", "data/models/uvsphere.obj", false, false );
				_attachMaterialToObject( "CyanColor", "UVsphere_defaultobject" );
				break;
			//Bunny
			case 2:
				loadFileTriangleMesh( "Bunny", "data/models/Bunny.obj", false, false );
				_attachMaterialToObject( "CyanColor", "Bunny_defaultobject" );
				break;
			//Bunny with AABB
			case 3:
				loadFileTriangleMesh( "Bunny", "data/models/Bunny.obj", true, false );
				_attachMaterialToObject( "CyanColor", "Bunny_defaultobject" );
				break;
			//Bunny with BVH
			case 4:
				loadFileTriangleMesh( "Bunny", "data/models/Bunny.obj", false, true );
				_attachMaterialToObject( "CyanColor", "Bunny_defaultobject" );
				break;

			default:
				loadFileTriangleMesh( "UVsphere", "data/models/uvsphere.obj", false, false );
				_attachMaterialToObject( "CyanColor", "UVsphere_defaultobject" );
				break;
			}

			// Pseudo Cornell box made with infinite planes .
			_addObject( new Plane( "PlaneGround", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
			_attachMaterialToObject( "GreyColor", "PlaneGround" );
			_addObject( new Plane( "PlaneLeft", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
			_attachMaterialToObject( "RedColor", "PlaneLeft" );
			_addObject( new Plane( "PlaneCeiling", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
			_attachMaterialToObject( "GreenColor", "PlaneCeiling" );
			_addObject( new Plane( "PlaneRight", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
			_attachMaterialToObject( "BlueColor", "PlaneRight" );
			_addObject( new Plane( "PlaneFront", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
			_attachMaterialToObject( "MagentaColor", "PlaneFront" );
			_addObject( new Plane( "PlaneRear", Vec3f( 0.f, 0.f, -10.f ), Vec3f( 0.f, 0.f, 1.f ) ) );
			_attachMaterialToObject( "YellowColor", "PlaneRear" );

			// ================================================================
			// Add lights .
			// ================================================================
			_addLight( new PointLight( Vec3f( 0.f, 3.f, -5.f ), WHITE, 100.f ) );
			break;


		//********TP5********
		case 5:
			if ( sceneToInit != 7 )
			{
				switch ( sceneToInit )
				{
				case 1:
					_addMaterial( new LambertMaterial( "SphereMat", GREY ) );
					break;

				case 2:
					_addMaterial( new MatteMaterial( "SphereMat", GREY, 0.6f ) );
					break;

				case 3:
					_addMaterial( new PlasticMaterial( "SphereMat", GREY, GREY, 64 ) );
					break;

				case 4:
					_addMaterial( new MetallicMaterial(
						"SphereMat", Vec3f( 1, 0.85, 0.57 ), Vec3f( 1, 0.85, 0.57 ), 0.f, 0.3f ) );
					break;

				case 5:
					_addMaterial( new MetallicMaterial(
						"SphereMat", Vec3f( 1, 0.85, 0.57 ), Vec3f( 1, 0.85, 0.57 ), 0.5f, 0.3f ) );
					break;

				case 6:
					_addMaterial( new MetallicMaterial(
						"SphereMat", Vec3f( 1, 0.85, 0.57 ), Vec3f( 1, 0.85, 0.57 ), 1.f, 0.3f ) );
					break;
				}

				_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );
				_attachMaterialToObject( "SphereMat", "Sphere1" );
				_addLight( new PointLight( Vec3f( 0.f, 0.f, -2.f ), WHITE, 60 ) );
			}
			else
			{
				_addMaterial( new MetallicMaterial( "BunnyMat", Vec3f( 1, 0.85, 0.57 ), Vec3f( 1, 0.85, 0.57 ), 0.7f, 0.3f ) );

				loadFileTriangleMesh( "Bunny", "data/models/Bunny.obj", false, true );
				_attachMaterialToObject( "BunnyMat", "Bunny_defaultobject" );
				_addLight( new PointLight( Vec3f( 0.f, 2.f, -6.f ), WHITE, 60 ) );
			}

			_addObject( new Plane( "Plane1", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
			_addMaterial( new LambertMaterial( "PlaneMat", RED ) );
			_attachMaterialToObject( "PlaneMat", "Plane1" );

			break;


		//********TP6********
		case 6: 
			// ================================================================
			// Add materials .
			// ================================================================
			_addMaterial( new MatteMaterial( " WhiteMatte ", WHITE, 0.6f ) );
			_addMaterial( new MatteMaterial( " RedMatte ", RED, 0.6f ) );
			_addMaterial( new MatteMaterial( " GreenMatte ", GREEN, 0.6f ) );
			_addMaterial( new MatteMaterial( " BlueMatte ", BLUE, 0.6f ) );
			_addMaterial( new MatteMaterial( " GreyMatte ", GREY, 0.6f ) );
			_addMaterial( new MatteMaterial( " MagentaMatte ", MAGENTA, 0.6f ) );
			_addMaterial( new MirrorMaterial( " Mirror " ) );
			_addMaterial( new TransparentMaterial( " Transparent " ) );

			// ================================================================
			// Add objects .
			// ================================================================
			_addObject( new Sphere( " Sphere1 ", Vec3f( -2.f, 0.f, 3.f ), 1.5f ) );
			_addObject( new Sphere( " Sphere2 ", Vec3f( 2.f, 0.f, 3.f ), 1.5f ) );
			_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );

			switch ( sceneToInit )
			{
			case 3:
				_attachMaterialToObject( " Mirror ", " Sphere1 " );
				_attachMaterialToObject( " WhiteMatte ", " Sphere2 " );
				_attachMaterialToObject( " MagentaMatte ", " PlaneFront " ); 
				break;
			case 4:
				_attachMaterialToObject( " Mirror ", " Sphere1 " );
				_attachMaterialToObject( " Mirror ", " Sphere2 " );
				_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );
				break;
			case 5:
				_attachMaterialToObject( " Mirror ", " Sphere1 " );
				_attachMaterialToObject( " Mirror ", " Sphere2 " );
				_attachMaterialToObject( " Mirror ", " PlaneFront " );
				break;
			case 6:
				_attachMaterialToObject( " Mirror ", " Sphere1 " );
				_attachMaterialToObject( " Transparent ", " Sphere2 " );
				_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );
				break;
			default:
				_attachMaterialToObject( " WhiteMatte ", " Sphere1 " );
				_attachMaterialToObject( " WhiteMatte ", " Sphere2 " );
				_attachMaterialToObject( " MagentaMatte ", " PlaneFront " ); 
			break;
			}

			// Pseudo Cornell box made with infinite planes .
			_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
			_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
			_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
			_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
			_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
			_attachMaterialToObject( " GreenMatte ", " PlaneCeiling " );
			_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
			_attachMaterialToObject( " BlueMatte ", " PlaneRight " );

			// ================================================================
			// Add lights .
			// ================================================================

			switch ( sceneToInit )
			{
			case 1: 
				_addLight( new PointLight( Vec3f( 0.f, 5.f, 0.f ), WHITE, 100.f ) ); 
				break;
			case 2:
				_addLight( new QuadLight( Vec3f( 1.f, 5.f, -2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 2.f ), WHITE, 40.f ) );
				break;
			default: 
				_addLight( new PointLight( Vec3f( 0.f, 5.f, 0.f ), WHITE, 100.f ) ); 
				break;
			}

			break;

			
		//********TP7********
		case 7:
			_addMaterial( new MatteMaterial( " WhiteMatte ", WHITE, 0.6f ) );
			_addMaterial( new MatteMaterial( " RedMatte ", RED, 0.6f ) );
			_addMaterial( new MatteMaterial( " GreenMatte ", GREEN, 0.6f ) );
			_addMaterial( new MatteMaterial( " BlueMatte ", BLUE, 0.6f ) );
			_addMaterial( new MatteMaterial( " GreyMatte ", GREY, 0.6f ) );
			_addMaterial( new MatteMaterial( " MagentaMatte ", MAGENTA, 0.6f ) );
			_addMaterial( new MirrorMaterial( " Mirror " ) );
			_addMaterial( new TransparentMaterial( " Transparent " ) );

			// Pseudo Cornell box made with infinite planes .
			_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
			_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
			_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
			_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
			_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
			_attachMaterialToObject( " GreenMatte ", " PlaneCeiling " );
			_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
			_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
			_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
			_attachMaterialToObject( " Mirror ", " PlaneFront " ); 
			
			switch ( sceneToInit )
			{
			case 1: 
				_addObject( new ImplicitSphere( " Implicit ", false, Vec3f( 0.f, 0.f, 3.f ), 1.f ) );
				break;

			case 2: 
				_addObject( new ImplicitCutHollowSphere( " Implicit ", false, Vec3f( 0.f, 0.f, 4.f ), 1.5f, 0.6f, 0.03f ) ); 
				break;

			case 3:
				_addObject( new ImplicitRoundedCylinder( " Implicit ", false, Vec3f( 0.f, 0.f, 4.f ), 1.f, 0.6f, 0.5f ) );
				break;

			case 4:
				_addObject( new ImplicitLink( " Implicit ", false, Vec3f( 0.f, 0.f, 4.f ), 1.f, 0.15f, 1.f ) );
				break;

			case 5:
				_addObject( new ImplicitLink( " ImplicitLink ", false, Vec3f( -2.f, 0.f, 2.f ), 0.7f, 0.3f, 0.4f ) );
				_addObject( new ImplicitRoundedCylinder( " ImplicitCylinder ", false, Vec3f( 0.f, 0.f, 4.f ), 0.7f, 0.6f, 0.5f ) );
				_addObject( new ImplicitCutHollowSphere( " ImplicitHollow ", false, Vec3f( 2.f, 0.f, 2.f ), 0.9f, 0.3f, 0.1f ) );
				_attachMaterialToObject( " GreenMatte ", " ImplicitLink " );
				_attachMaterialToObject( " BlueMatte ", " ImplicitCylinder " );
				_attachMaterialToObject( " RedMatte ", " ImplicitHollow " );
				break;
			default: 
				break;
			}
			_attachMaterialToObject( " MagentaMatte ", " Implicit " );

			_addLight( new PointLight( Vec3f( 0.f, 5.f, 0.f ), WHITE, 100.f ) ); 
			
			break;

		//********Projet********
		case 8:
			_addMaterial( new MatteMaterial( " WhiteMatte ", WHITE, 0.6f ) );
			_addMaterial( new MatteMaterial( " RedMatte ", RED, 0.6f ) );
			_addMaterial( new MatteMaterial( " GreenMatte ", GREEN, 0.6f ) );
			_addMaterial( new MatteMaterial( " BlueMatte ", BLUE, 0.6f ) );
			_addMaterial( new MatteMaterial( " GreyMatte ", GREY, 0.6f ) );
			_addMaterial( new MatteMaterial( " MagentaMatte ", MAGENTA, 0.6f ) );
			_addMaterial( new MirrorMaterial( " Mirror " ) );
			_addMaterial( new TransparentMaterial( " Transparent " ) );
			_addMaterial( new MetallicMaterial( " Gold ", Vec3f( 1, 0.85, 0.57 ), Vec3f( 1, 0.85, 0.57 ), 1.f, 0.3f ) );
			_addMaterial( new MetallicMaterial( " Silver ", Vec3f( 0.8, 0.8, 0.8 ), Vec3f( 0.8, 0.8, 0.8 ), 1.f, 0.3f ) );

			switch ( sceneToInit )
			{
			case 1:
				_addObject( new Sphere( " Sphere1 ", Vec3f( -2.f, 0.f, 8.f ), 1.5f ) );
				_addObject( new Sphere( " Sphere2 ", Vec3f( 2.f, 0.f, 3.f ), 1.5f ) );
				_addObject( new Sphere( " Sphere3 ", Vec3f( 0.f, 1.f, 16.f ), 1.5f ) );
				_attachMaterialToObject( " RedMatte ", " Sphere1 " );
				_attachMaterialToObject( " MagentaMatte ", " Sphere2 " );
				_attachMaterialToObject( " BlueMatte ", " Sphere3 " );
				_addLight( new PointLight( Vec3f( 0.f, 6.f, 15.f ), WHITE, 50.f ) );
				_addLight( new PointLight( Vec3f( 0.f, 6.f, 6.f ), WHITE, 100.f ) );
				_addLight( new PointLight( Vec3f( 0.f, 6.f, 2.f ), WHITE, 100.f ) );
				break;

			case 2:
				_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
				_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
				_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
				_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
				_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
				_attachMaterialToObject( " GreenMatte ", " PlaneCeiling " );
				_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
				_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
				_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
				_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );
				_addObject( new ImplicitLink( " ImplicitLink ", true, Vec3f( -2.f, 0.f, 2.f ), 1.f, 0.4f, 1.f ) );
				_addObject( new ImplicitSphere( " ImplicitSphere ", true, Vec3f( 0.f, 0.f, 2.f ), 1.5f ) );
				_addObject( new ImplicitCutHollowSphere( " ImplicitCutHollowSphere ", true, Vec3f( 2.f, 0.f, 2.f ), 1.5f, 0.6f, 0.03f ) ); 
				_attachMaterialToObject( " GreenMatte ", " ImplicitLink " );
				_attachMaterialToObject( " BlueMatte ", " ImplicitSphere " );
				_attachMaterialToObject( " RedMatte ", " ImplicitCutHollowSphere " );
				_addLight( new PointLight( Vec3f( 0.f, 0.f, -5.f ), WHITE, 100.f ) );
				_addLight( new PointLight( Vec3f( 0.f, 3.f, 2.f ), WHITE, 100.f ) );
				break;

			case 4: 
			case 3:
				_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
				_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
				_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
				_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
				_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
				_attachMaterialToObject( " GreenMatte ", " PlaneCeiling " );
				_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
				_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
				_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
				_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );
				_addObject( new ImplicitMandelbulb( " Mandelbulb ", false, Vec3f( 0.f, 0.f, 3.f )) );
				_attachMaterialToObject( " Gold ", " Mandelbulb " );
				_addLight( new PointLight( Vec3f( 0.f, 0.f, -6.f ), WHITE, 100.f ) );
				_addLight( new PointLight( Vec3f( 0.f, 3.f, 2.f ), WHITE, 100.f ) );
				break;
			case 5:
				_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -1.5f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
				_attachMaterialToObject( " Silver ", " PlaneGround " );
				_addObject( new Plane( " PlaneLeft ", Vec3f( 2.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
				_attachMaterialToObject( " Mirror ", " PlaneLeft " );
				_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 1.5f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
				_attachMaterialToObject( " Mirror ", " PlaneCeiling " );
				_addObject( new Plane( " PlaneRight ", Vec3f( -2.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
				_attachMaterialToObject( " Mirror ", " PlaneRight " );
				_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 5.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
				_attachMaterialToObject( " Mirror ", " PlaneFront " );
				_addObject( new Plane( " PlaneBack ", Vec3f( 0.f, 0.f, -5.f ), Vec3f( 0.f, 0.f, 1.f ) ) );
				_attachMaterialToObject( " Mirror ", " PlaneBack " );
				_addObject( new ImplicitMandelbulb( " Mandelbulb ", false, Vec3f( 0.f, 0.f, 3.f ) ) );
				_attachMaterialToObject( " Gold ", " Mandelbulb " );
				_addObject( new ImplicitLink( " ImplicitLink ", false, Vec3f( 0.f, -0.5f, 5.f ), 1.9f, 0.3f, 0.2f ) );
				_attachMaterialToObject( " Silver ", " ImplicitLink " );
				_addLight( new PointLight( Vec3f( 0.f, 0.f, -2.f ), WHITE, 10.f ) );
				_addLight( new PointLight( Vec3f( 0.f, 0.f, 2.f ), WHITE, 10.f ) );
				_addLight( new PointLight( Vec3f( 0.f, 1.2f, 0.f ), WHITE, 10.f ) );
				//_addLight( new QuadLight( Vec3f( 0.f, 0.f, -6.f ), Vec3f( -2, 0, 0 ), Vec3f( 0, 0, 2 ), WHITE, 100.f ) );
				//_addLight( new QuadLight( Vec3f( 0.f, 3.f, 2.f ), Vec3f( -2, 0, 0 ), Vec3f( 0, 0, 2 ), WHITE, 100.f ) );
				break;
			}

			break;

		default:
			// Add objects.
			_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

			// Add materials.
			_addMaterial( new ColorMaterial( "Blue", BLUE ) );

			// Link objects and materials.
			_attachMaterialToObject( "Blue", "Sphere1" );
			break;
		}
	}

	void Scene::loadFileTriangleMesh( const std::string & p_name, const std::string & p_path, bool useAABB, bool useBVH )
	{
		std::cout << "Loading: " << p_path << std::endl;
		Assimp::Importer importer;

		// Read scene and triangulate meshes
		const aiScene * const scene
			= importer.ReadFile( p_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords );

		if ( scene == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path ); }

		unsigned int cptTriangles = 0;
		unsigned int cptVertices  = 0;

		for ( unsigned int m = 0; m < scene->mNumMeshes; ++m )
		{
			const aiMesh * const mesh = scene->mMeshes[ m ];
			if ( mesh == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path + ": mesh is null" ); }

			const std::string meshName = p_name + "_" + std::string( mesh->mName.C_Str() );
			std::cout << "-- Load mesh " << m + 1 << "/" << scene->mNumMeshes << ": " << meshName << std::endl;

			cptTriangles += mesh->mNumFaces;
			cptVertices += mesh->mNumVertices;

			const bool hasUV = mesh->HasTextureCoords( 0 );

			MeshTriangle * triMesh = new MeshTriangle( meshName, useAABB, useBVH );
			// Vertices before faces otherwise face normals cannot be computed.
			for ( unsigned int v = 0; v < mesh->mNumVertices; ++v )
			{
				triMesh->addVertex( mesh->mVertices[ v ].x, mesh->mVertices[ v ].y, mesh->mVertices[ v ].z );
				triMesh->addNormal( mesh->mNormals[ v ].x, mesh->mNormals[ v ].y, mesh->mNormals[ v ].z );
				if ( hasUV ) triMesh->addUV( mesh->mTextureCoords[ 0 ][ v ].x, mesh->mTextureCoords[ 0 ][ v ].y );
			}
			for ( unsigned int f = 0; f < mesh->mNumFaces; ++f )
			{
				const aiFace & face = mesh->mFaces[ f ];
				triMesh->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}

			if ( useBVH )
			{
				triMesh->buildBVH(); 
			}
			_addObject( triMesh );

			const aiMaterial * const mtl = scene->mMaterials[ mesh->mMaterialIndex ];
			if ( mtl == nullptr )
			{
				std::cerr << "Material undefined," << meshName << " assigned to default material" << std::endl;
			}
			else
			{
				Vec3f kd = WHITE;
				Vec3f ks = BLACK;
				float s	 = 0.f;

				aiColor3D aiKd;
				if ( mtl->Get( AI_MATKEY_COLOR_DIFFUSE, aiKd ) == AI_SUCCESS ) kd = Vec3f( aiKd.r, aiKd.g, aiKd.b );
				aiColor3D aiKs;
				if ( mtl->Get( AI_MATKEY_COLOR_SPECULAR, aiKs ) == AI_SUCCESS ) ks = Vec3f( aiKs.r, aiKs.g, aiKs.b );
				float aiS = 0.f;
				if ( mtl->Get( AI_MATKEY_SHININESS, aiS ) == AI_SUCCESS ) s = aiS;
				aiString mtlName;
				mtl->Get( AI_MATKEY_NAME, mtlName );

				/* _addMaterial( new ColorMaterial( std::string( mtlName.C_Str() ), kd ) );
				_attachMaterialToObject( mtlName.C_Str(), meshName );*/
			}

			std::cout << "-- [DONE] " << triMesh->getNbTriangles() << " triangles, " << triMesh->getNbVertices()
					  << " vertices." << std::endl;
		}
		std::cout << "[DONE] " << scene->mNumMeshes << " meshes, " << cptTriangles << " triangles, " << cptVertices
				  << " vertices." << std::endl;
	}

	bool Scene::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersect( p_ray, p_tMin, tMax, p_hitRecord ) )
			{
				tMax = p_hitRecord._distance; // update tMax to conserve the nearest hit
				hit	 = true;
			}
		}
		return hit;
	}

	bool Scene::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersectAny( p_ray, p_tMin, p_tMax ) ) { return true; }
		}
		return false;
	}

	void Scene::_addObject( BaseObject * p_object )
	{
		const std::string & name = p_object->getName();
		if ( _objectMap.find( name ) != _objectMap.end() )
		{
			std::cout << "[Scene::addObject] Object \'" << name << "\' already exists" << std::endl;
			delete p_object;
		}
		else
		{
			_objectMap[ name ] = p_object;
			_objectMap[ name ]->setMaterial( _materialMap[ "default" ] );
		}
	}

	void Scene::_addMaterial( BaseMaterial * p_material )
	{
		const std::string & name = p_material->getName();
		if ( _materialMap.find( name ) != _materialMap.end() )
		{
			std::cout << "[Scene::_addMaterial] Material \'" << name << "\' already exists" << std::endl;
			delete p_material;
		}
		else
		{
			std::cout << "Material \'" << name << "\' added." << std::endl;
			_materialMap[ name ] = p_material;
		}
	}

	void Scene::_addLight( BaseLight * p_light ) { _lightList.emplace_back( p_light ); }

	void Scene::_attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName )
	{
		if ( _objectMap.find( p_objectName ) == _objectMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Object \'" << p_objectName << "\' does not exist"
					  << std::endl;
		}
		else if ( _materialMap.find( p_materialName ) == _materialMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Material \'" << p_materialName << "\' does not exist, "
					  << "object \'" << p_objectName << "\' keeps its material \'"
					  << _objectMap[ p_objectName ]->getMaterial()->getName() << "\'" << std::endl;
		}
		else
		{
			_objectMap[ p_objectName ]->setMaterial( _materialMap[ p_materialName ] );
		}
	}

} // namespace RT_ISICG
