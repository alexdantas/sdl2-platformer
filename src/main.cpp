#include "SDL.hpp"
#include "Window.hpp"

#include <exception>
#include "StateManager.hpp"
#include "Config.hpp"
#include "Log.hpp"

#include "Sprite.hpp"

/// Starting point of the game.
///
/// Thank you for having the trouble of looking out my code!
///
/// # Note for developers
///
/// Sorry for disappointing you.
/// This function's so small because everything is handled on the
/// `StateManager` class. It decides what to do based on the
/// current game state (for example the main menu, or game over
/// screen).
///
/// If you want to understand the code, I suggest you to read the
/// `StateManager` first - just to get an idea on how the states are
/// switched.
///
/// Then, you may see the individual state files, on the order
/// of appearance (you can check that on `StateManager::run()`.
///
int main()
{
	try
	{
		Config::load("config.ini");

		if (Config::getBool("debug", false))
		{
			Log::debugMode(true);
			Log::verboseMode(true);
		}

		SDL::init();

		int width  = Config::getInt("width",  640);
		int height = Config::getInt("height", 480);

		Window window(width, height, "SDL2 Platformer");
		window.setBackgroundColor(Color("white"));

		// Sprite sprite(&window, "images/bg.png");
		// sprite.render(0, 0);
		// window.refresh();
		// SDL_Delay(1000);
		// window.clear();
		// sprite.render(0, 0);
		// window.refresh();
		// SDL_Delay(1000);
		// return 0;

		StateManager manager(&window);

		manager.run(); // main loop of the game

		SDL::exit();
	}
	catch (...)
	{
		// I dont really have a nice exception-handling scheme right
		// now. I must learn how to properly deal with them.
		// As of now, everything that fucks up gets the program
		// terminated.
		Log::error("Exception caught! Quitting...");
		return -1;
	}
	return 0;
}

