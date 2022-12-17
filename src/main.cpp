#include <SDL.h>
#include <SDL_mixer.h>
#include "mixer.h"
#include "input.h"
#include "engine.h"
#include "window.h"
#include "texture.h"
#include "renderer.h"
#include "utility/timer.h"

/* main.cpp:
   The entry point of the program. */

int main(int argc, char* argv[])
{
	IF_DEBUG
	{
		lyo::Engine::Log << "Command-line arguments:\n";

		for (int i{ 0 }; i < argc; ++i)
			lyo::Engine::Log << i + 1 << ". " << argv[i] << '\n';

		lyo::Engine::Log << '\n';
	}

	lyo::Engine engine	{ SDL_INIT_VIDEO | SDL_INIT_AUDIO };
	lyo::Mixer	mixer	{ MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048 };
	lyo::Input	input;

	lyo::Window window	{ "lyoEngine v" LYOENGINE_VERSION, mixer, input, {}, SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC };

	lyo::Texture texture{ window, "assets/backgrounds/hell.png" };

	if (argc > 1)
		texture = argv[1];	

	lyo::Slider<double> scale{ 1.0, 0.1, 10.0 };
	lyo::Slider<double>	angle{ 0.0, -360.0, 360.0 };

	lyo::Timer timer;

	constexpr double	SCALE_PER_SEC{ 1.0 };
	constexpr float		ANGLE_PER_SEC{ 150.0 };

	while (!input.pressed(SDL_SCANCODE_ESCAPE))
	{
		input.update();

		if (input.held(SDL_SCANCODE_S))
			scale += SCALE_PER_SEC * timer;
			
		if (input.held(SDL_SCANCODE_W))
			scale -= SCALE_PER_SEC * timer;

		if (input.held(SDL_SCANCODE_A))
			angle -= ANGLE_PER_SEC * timer;

		if (input.held(SDL_SCANCODE_D))
			angle += ANGLE_PER_SEC * timer;

		if (input.pressed(SDL_SCANCODE_LMB))
			scale = 1.0;

		if (input.pressed(SDL_SCANCODE_RMB))
			angle = 0.0;

		timer.reset();

		texture.set_scale(scale);
		texture.update();
		texture.draw({ window.width() / 2.0 - texture.width() / 2.0, window.height() / 2.0 - texture.height() / 2.0}, angle);

		window.draw();
	}
		
	return EXIT_SUCCESS;
}