#include <SDL.h>

#include "text.h"
#include "mixer.h"
#include "input.h"
#include "engine.h"
#include "entity.h"
#include "window.h"
#include "globals.h"
#include "renderer.h"

/* main.cpp:
   The entry point of the program. */

int main(int argc, char* argv[])
{
	IF_DEBUG
	{
		lyo::Engine::Log << "Command-line arguments:\n";

		for (int i{ 0 }; i < argc; ++i)
			lyo::Engine::Log << i + 1 << ". " << argv[i] << '\n';

		lyo::Engine::Log << std::endl;
	}

	const lyo::Engine engine{SDL_INIT_VIDEO | SDL_INIT_AUDIO};

	lyo::Mixer mixer;
	lyo::Input input;
	
	lyo::Window window{ "lyoEngine " LYOENGINE_VERSION, mixer, input };

	const lyo::Font engine_font	{ FONT("montserrat.ttf"), 48 };

	mixer.music = "assets/music/checkpoint.mp3";
	mixer.music.play(4.0, 0);

	{
		lyo::Texture logo{ window, "assets/sprites/haloda.png", 3.0 };
		logo.set_area({ 192, 0, 64, 64 });
		logo.opacity = 1.0;

		lyo::Font m5x7{ FONT("m5x7.ttf"), 72 };

		lyo::Text load{ window, m5x7, "A game by IdleFour" };
		load.opacity = 1.0;

		lyo::Coordinate logo_cnt{ logo.center() }, load_cnt{ load.center() };

		logo_cnt.y = load.height() + 450.0, load_cnt.y = 400.0;

		constexpr double OPACITY_INCR{ 150.0 }, OPACITY_DECR{ OPACITY_INCR * 1.5 };

		lyo::Timer menu_timer;

		while (load.opacity != load.opacity.max() && !input.pressed(SDL_SCANCODE_ESCAPE) && !input.pressed(SDL_SCANCODE_RETURN))
		{
			load.opacity += OPACITY_INCR * menu_timer;
			logo.opacity += OPACITY_INCR * menu_timer;

			menu_timer.reset();

			load.update();
			logo.update();

			load.draw(load_cnt);
			logo.draw(logo_cnt);

			window.draw();

			input.update();
		}

		while (!input.pressed(SDL_SCANCODE_ESCAPE) && !input.pressed(SDL_SCANCODE_RETURN))
		{
			input.update();
		}
		
		menu_timer.reset();
		mixer.music.halt(load.opacity / OPACITY_DECR);

		while (load.opacity != load.opacity.min() && !input.pressed(SDL_SCANCODE_ESCAPE))
		{
			load.opacity -= OPACITY_DECR * menu_timer;
			logo.opacity -= OPACITY_DECR * menu_timer;

			menu_timer.reset();

			load.update();
			logo.update();

			load.draw(load_cnt);
			logo.draw(logo_cnt);

			window.draw();

			input.update();
		}
		
		window.draw();
	}

	lyo::Text	text{ window, engine_font, argc > 1 ? argv[1] : "lyoEngine " LYOENGINE_VERSION " developement build", 0x19F4FF },
				time{ window, engine_font, "Frametime" },
				scl{ window, engine_font, "Scale" },
				rot{ window, engine_font, "Angle" },
				dt{ window, engine_font, "Delta time" };

	lyo::Entity ent{ window, "assets/sprites/haloda.png", { { Animation::Idle, SC<lyo::u8>(8) }, {Animation::Attack, SC<lyo::u8>(8) } }, {64, 64}, {0, 0}};

	ent.opacity = 0.0;
	ent.update();
	ent.set_position(ent.center());

	lyo::StaticSlider<double, -360.0, 360.0>	angle;
	lyo::StaticSlider<double, 1.0, 10.0>		scale{ ent.scale() };

	constexpr double ANGLE_PER_SEC{ 135.0 }, SCALE_PER_SEC{ 10.0 };

	lyo::Timer timer;

	lyo::String rt{ "Runtime: " }, sc{ "Scale: " }, ag{ "Angle: " }, dl{ "Delta time: " };
	
	if (!input.pressed(SDL_SCANCODE_ESCAPE))
	{
		ent.opacity = 255.0;
		ent.update();
	}

	mixer.music = "assets/music/negotiations_over.mp3";
	mixer.music.play();

	while (!input.pressed(SDL_SCANCODE_ESCAPE))
	{
		if (input.held(SDL_SCANCODE_S))
			scale += SCALE_PER_SEC * timer;

		if (input.held(SDL_SCANCODE_W))
			scale -= SCALE_PER_SEC * timer;

		if (input.held(SDL_SCANCODE_A))
			angle -= ANGLE_PER_SEC * timer;

		if (input.held(SDL_SCANCODE_D))
			angle += ANGLE_PER_SEC * timer;

		if (input.pressed(SDL_SCANCODE_LMB))
			scale = lyo::Settings::Default_Scale;

		if (input.pressed(SDL_SCANCODE_RMB))
			angle = 0.0;

		if (input.pressed(SDL_SCANCODE_BACKSPACE))
			ent.set_animation(Animation::Attack);

		if (input.pressed(SDL_SCANCODE_RETURN))
			ent.set_animation(Animation::Idle);

		time	= rt + std::to_string(g::runtime).c_str();
		scl		= sc + std::to_string(scale).c_str();
		rot		= ag + std::to_string(angle).c_str();
		dt		= dl + std::to_string(timer).c_str();

		timer.reset();

		text.draw	({ 20, 10 });
		time.draw	({ 20, SC<double>(10 + text.height()) });
		scl.draw	({ 20, SC<double>(10 + text.height() + time.height()) });
		rot.draw	({ 20, SC<double>(10 + text.height() + time.height() + scl.height()) });
		dt.draw		({ 20, SC<double>(10 + text.height() + time.height() + scl.height() + rot.height()) });

		ent.set_scale(scale);
		ent.set_angle(angle);

		ent.set_position(ent.center());
		ent.update();

		window.draw();

		input.update();
	}

	constexpr double FADE_OUT_INCR{ 255.0 };

	while (ent.opacity != ent.opacity.min())
	{
		ent.opacity -= FADE_OUT_INCR * timer;

		timer.reset();

		ent.update();

		window.draw();
	}

	return EXIT_SUCCESS;
}