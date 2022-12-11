#include <SDL.h>
#include <SDL_mixer.h>
#include "mixer.h"
#include "input.h"
#include "engine.h"
#include "window.h"
#include "texture.h"
#include "renderer.h"

/* main.cpp:
   The entry point of the program. */

int main(int argc, char* argv[])
{
	lyo::Engine		lyoEngine	{ SDL_INIT_VIDEO | SDL_INIT_AUDIO };
	lyo::Window		window		{ "lyoEngine", {10, 20}, SDL_WINDOW_FULLSCREEN_DESKTOP };
	lyo::Renderer	renderer	{ window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC };
	lyo::Mixer		DJ			{ MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048 };
	lyo::Input		input;

	lyo::Texture txt{ renderer, "assets/sprites/controls.png", SDL_BLENDMODE_BLEND };
	lyo::Engine::Log << "texture size is " << txt.width() << "x" << txt.height() << '\n';
	
	while (!input.pressed(SDL_SCANCODE_ESCAPE))
	{
		input.update();

		txt.draw(txt.area(), { 0.0, 0.0 }, 0.0, SDL_FLIP_NONE);

		renderer.present();
		renderer.clear();
	}

	return EXIT_SUCCESS;
}