#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/direct_lighting_integrator.hpp"
#include "integrators/whitted_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::WHITTED: 
			_integrator = new WhittedIntegrator(); 
			break;

		case IntegratorType::DIRECT_LIGHTING: 
			_integrator = new DirectLightingIntegrator();
			break;

		case IntegratorType::RAY_CAST:
		default:
		{
			_integrator = new RayCastIntegrator();
			break;
		}
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();
		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				/// TODO !
				Vec3f value = VEC3F_ZERO;
				for ( int nbRayons = 0; nbRayons < _nbPixelSamples; nbRayons++ ) {
					float rx = randomFloat();
					float ry = randomFloat();  
					Ray ray = p_camera->generateRay( (float)(i + rx) / (float)( width - 1 ) , (float)(j + ry) / (float)( height - 1 ) );
					float p_t1 = 0, p_t2 = 100;
					value += _integrator->Li( p_scene, ray, p_t1, p_t2 );
				}
				p_texture.setPixel( i, j, glm::clamp( value / (float)_nbPixelSamples, 0.f, 1.f ) );
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}


	
	float Renderer::renderImageDOF( const Scene & p_scene, PerspectiveCamera * p_cameras[], Texture & p_texture, const int nbCams )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		const int nbCameras = nbCams;

		progressBar.start( height * nbCameras, 50 );
		chrono.start();	
		std::vector<std::vector<Vec3f>> pixelValue;

		for ( int j = 0; j < width; j++ )
		{
			std::vector<Vec3f> row;
			for ( int i = 0; i < height; i++ )
			{
				row.push_back( VEC3F_ZERO );
			}
			pixelValue.push_back( row );
		}

		#pragma omp parallel for
		for ( int id = 0; id < nbCameras; id++ )
		{
			for ( int j = 0; j < height; j++ )
			{
				for ( int i = 0; i < width; i++ )
				{
					/// TODO !
					Vec3f value = VEC3F_ZERO;
					for ( int nbRayons = 0; nbRayons < _nbPixelSamples; nbRayons++ )
					{
						float rx   = randomFloat();
						float ry   = randomFloat();
						Ray	  ray  = p_cameras[ id ]->generateRay( (float)( i + rx ) / (float)( width - 1 ),
																   (float)( j + ry ) / (float)( height - 1 ) );
						float p_t1 = 0, p_t2 = 100;
						value += _integrator->Li( p_scene, ray, p_t1, p_t2 );
					}
					pixelValue.at( i ).at( j ) += glm::clamp( value / (float)_nbPixelSamples, 0.f, 1.f );
				}
				progressBar.next();
			}
		}

		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				p_texture.setPixel( i, j, glm::clamp( pixelValue.at( i ).at( j ) / (float)nbCameras, 0.f, 1.f ) );
			}
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
