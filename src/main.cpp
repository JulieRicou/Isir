#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		int tpToInit	  = 8;
		int sceneToInit	  = 5;
		int pixelsSamples = 64;
		int lightSamples  = 32;

		//const int imgWidth	= 600;
		//const int imgHeight = 400;
		const int imgWidth	= 1920;
		const int imgHeight = 1080;

		// Create a texture to render the scene.
		Texture img = Texture( imgWidth, imgHeight );

		// Create and init scene.
		Scene scene;
		scene.init( tpToInit, sceneToInit );

		// Create the renderer.
		Renderer renderer;

		// Create a perspective camera.
		PerspectiveCamera * camera;

		// Depth of field parameters
		PerspectiveCamera * cameras[ 64 ];
		const int			nbCams = 64;
		const float			aperture = 0.05;
		Vec3f			focus	 = Vec3f( 0, 0, 3.f );
		Vec3f			camPosition	 = Vec3f( 0, 0, -2.f );
		bool				useDOF		= false;

		switch ( tpToInit )
		{
		//********TP1********
		case 1:
			switch ( sceneToInit )
			{
			case 4:
				camera = new PerspectiveCamera( Vec3f( 4.f, -1.f, 0.f ),
												Vec3f( -1.f, -1.f, 2.f ),
												Vec3f( 0, 1.f, 0 ),
												60.f,
												float( imgWidth ) / imgHeight );
				break;
			case 3:
				camera = new PerspectiveCamera( Vec3f( 0.f, 1.f, 0.f ),
												Vec3f( 0.f, 1.f, 1.f ),
												Vec3f( 0, 1.f, 0 ),
												60.f,
												float( imgWidth ) / imgHeight );
				break;
			case 2:
				camera = new PerspectiveCamera( Vec3f( 1.f, 0.f, 0.f ),
												Vec3f( 1.f, 0, 1.f ),
												Vec3f( 0, 1.f, 0 ),
												60.f,
												float( imgWidth ) / imgHeight );
				break;
			default:
				camera = new PerspectiveCamera( Vec3f( 0, 0.f, -2.f ),
												Vec3f( 0, 0, 79.f ),
												Vec3f( 0, 1.f, 0 ),
												60.f,
												float( imgWidth ) / imgHeight );
			}

			renderer.setIntegrator( IntegratorType::RAY_CAST );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;


		//********TP2********
		case 2:
			camera = new PerspectiveCamera(
				Vec3f( 0, 0.f, -2.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;


		//********TP3********
		case 3:
			camera = new PerspectiveCamera(
				Vec3f( 0, 0.f, -2.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;

		//********TP4********
		case 4:
			camera = new PerspectiveCamera(
				Vec3f( 0, 2.f, -6.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;


		//********TP5********
		case 5:
			if (sceneToInit != 7)
			{
				camera = new PerspectiveCamera( Vec3f( 0, 0.f, 0.f ), Vec3f( 0, 0, 1.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );
			}
			else
			{
				camera = new PerspectiveCamera( Vec3f( 0, 0.f, -4.f ), Vec3f( 0, 0, 1.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );
			}

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;


		//********TP6********
		case 6:
			camera = new PerspectiveCamera( Vec3f( 0, 2.f, -6.f ), Vec3f( 0, 2.f, 1.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			switch ( sceneToInit )
			{
			case 3:
			case 4:
			case 5:
			case 6:
				renderer.setIntegrator( IntegratorType::WHITTED );
				break;
			default:

				renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
				break;
			}
			renderer.setBackgroundColor( BLACK );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;

			
		//********TP7********
		case 7: 
			camera = new PerspectiveCamera( Vec3f( 0, 2.f, -6.f ), Vec3f( 0, 2.f, 1.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );
			renderer.setIntegrator( IntegratorType::WHITTED );
			renderer.setBackgroundColor( BLACK );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );

			break;

		//********Projet********
		case 8:

			camera = new PerspectiveCamera( Vec3f( 0, 2.f, -6.f ), Vec3f( 0, 2.f, 1.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			switch ( sceneToInit )
			{
			case 1: 
				camPosition = Vec3f( 0, 0.f, -2.f );
				focus = Vec3f( 0, 0, 3.f );
				useDOF		= true;
				renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING ); 
				break;
			case 2: 
				camera = new PerspectiveCamera( Vec3f( 0, 0.f, -6.f ),
												Vec3f( 0, 0.f, 1.f ),
												Vec3f( 0, 1.f, 0 ),
												60.f,
												float( imgWidth ) / imgHeight );
				renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING ); 
				break;
			case 3:
				camera = new PerspectiveCamera( Vec3f( 0, 0.f, -3.f ),
												Vec3f( 0, 0.f, 1.f ),
												Vec3f( 0, 1.f, 0 ),
												60.f,
												float( imgWidth ) / imgHeight );
				renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING ); 
				break;
			case 4:
				camera		= new PerspectiveCamera( Vec3f( 0.25f, 0.75f, -1.f ),
												 Vec3f( 0.25f, 0.75f, 1.f ),
												 Vec3f( 0, 1.f, 0 ),
												 60.f,
												float( imgWidth ) / imgHeight );
				renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING ); 
				break;

			case 5:
				camPosition = Vec3f( 0, 1.4f, -4.9f );
				focus		= Vec3f( 0, 1.4f, 0.f );
				useDOF		= true;
				renderer.setIntegrator( IntegratorType::WHITTED ); 
				break;
			default: break;
			}
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;

		default:

			camera = new PerspectiveCamera(
				Vec3f( 0, 0.f, -2.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;
		}

		// Launch rendering.
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = 0;

		if (useDOF) {
			cameras[ 0 ]
				= new PerspectiveCamera( camPosition, focus, Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			for ( size_t i = 1; i < nbCams; i++ )
			{
				cameras[ i ] = new PerspectiveCamera( Vec3f( ( randomFloat() - 0.5f ) * aperture + camPosition.x,
															 ( randomFloat() - 0.5f ) * aperture + camPosition.y,
															 camPosition.z ),
													  focus,
													  Vec3f( 0, 1.f, 0 ),
													  60.f,
													  float( imgWidth ) / imgHeight );
			}
			renderingTime = renderer.renderImageDOF( scene, cameras, img, nbCams );
		}
		else { 
			renderingTime = renderer.renderImage( scene, camera, img );
		}

		std::cout << "-> Done in " << renderingTime << "ms" << std::endl;

		// Save rendered image.
		const std::string imgName = "image.jpg";
		img.saveJPG( RESULTS_PATH + imgName );

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::main( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Exception caught:" << std::endl << e.what() << std::endl;
	}
}