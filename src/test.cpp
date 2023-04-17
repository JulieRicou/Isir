#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	class test
	{
	  public:
		int thetest( int argc, char ** argv )
		{
			const int imgWidth	= 600;
			const int imgHeight = 400;

			// Create a texture to render the scene.
			Texture img = Texture( imgWidth, imgHeight );

			// Create and init scene.
			Scene scene;
			scene.init();

			// Create a perspective camera.
			// PerspectiveCamera camera( float( imgWidth ) / imgHeight );

			int				  cameraParameters = 1;
			PerspectiveCamera camera(
				Vec3f( 0, 2.f, -7.f ), Vec3f( 0, 0, 79.f ), Vec3f( 0, 1.f, 0 ), 60.f, float( imgWidth ) / imgHeight );
			// PerspectiveCamera camera( Vec3f( 0, 0.f, 0.f ), Vec3f( 0, 0, 1.f ), Vec3f( 0, 1.f, 0 ), 60.f, float(
			// imgWidth ) / imgHeight );

			// Create and setup the renderer.
			Renderer renderer;
			renderer.setIntegrator( IntegratorType::DIRECT_LIGHTING );
			renderer.setBackgroundColor( GREY );
			renderer.setNbPixelSamples( 1 );
			renderer.setLightSamples( 1 );

			// Launch rendering.
			std::cout << "Rendering..." << std::endl;
			std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

			float renderingTime = renderer.renderImage( scene, &camera, img );

			std::cout << "-> Done in " << renderingTime << "ms" << std::endl;

			// Save rendered image.
			const std::string imgName = "image.jpg";
			img.saveJPG( RESULTS_PATH + imgName );

			return EXIT_SUCCESS;
		}
	};
} // namespace RT_ISICG