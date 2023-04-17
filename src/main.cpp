#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		int tpToInit	  = 5;
		int sceneToInit	  = 4;
		int pixelsSamples = 32;
		int lightSamples = 1;

		const int imgWidth	= 600;
		const int imgHeight = 400;

		// Create a texture to render the scene.
		Texture img = Texture( imgWidth, imgHeight );

		// Create and init scene.
		Scene scene;
		scene.init( tpToInit, sceneToInit );

		// Create the renderer.
		Renderer renderer;

		// Create a perspective camera.
		PerspectiveCamera * camera;

		switch ( tpToInit )
		{
		//****TP1****
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

		//****TP2****
		case 2:
			camera = new PerspectiveCamera(
				Vec3f( 0, 0.f, -2.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;

		//****TP3****
		case 3:
			camera = new PerspectiveCamera(
				Vec3f( 0, 0.f, -2.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;

		//****TP4****
		case 4:
			camera = new PerspectiveCamera(
				Vec3f( 0, 2.f, -6.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;

		//****TP5****
		case 5:
			camera = new PerspectiveCamera(
				Vec3f( 0, 0.f, 0.f ), Vec3f( 0, 0, 1.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;

		default:
			camera = new PerspectiveCamera(
				Vec3f( 0, 0.f, -2.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );

			renderer.setIntegrator( IntegratorType::RAY_CAST );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( pixelsSamples );
			renderer.setLightSamples( lightSamples );
			break;
		}

		// Launch rendering.
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = renderer.renderImage( scene, camera, img );

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