#include <cstdlib>              // srand()
#include <ctime>                // time()
#include "StateManager.hpp"
#include "SDL.hpp"
#include "Log.hpp"
#include "Config.hpp"
#include "GameStateGame.hpp"
#include "Window.hpp"

StateManager::StateManager(Window* window):
	window(window),
	currentState(nullptr),
	sharedInfo(0)
{
	this->currentState = new GameStateGame(this->window);

	this->currentState->load();
	this->sharedInfo = 0;

	srand(time(nullptr));
}
StateManager::~StateManager()
{
	if (this->currentState)
	{
		this->currentState->unload();
		delete this->currentState;

		this->currentState = nullptr; // you never know
	}
}
void StateManager::run()
{
	bool letsQuit = false;

	bool firstFrame = true;

	while (!letsQuit)
	{
		// How many milliseconds the last frame took
		unsigned int delta_ms = this->window->getDelta();

		// How many seconds have passed between last
		// frame and this one?
		float delta = (float)(delta_ms)/1000.0;

		// Little hack to avoid things jumping around
		// on the first frame.
		if (firstFrame)
		{
			delta = 1000.0/30.0;
			firstFrame = false;
		}

		// Just a reminder that every state handles input
		// individually, so no need to do that here.

		// Updating the whole state.
		// This value is returned from it tell us if
		// we need to switch from the current state.
		GameState::StateCode whatToDoNow;

		whatToDoNow = this->currentState->update(delta);

		switch (whatToDoNow)
		{
		case GameState::CONTINUE:
			// Just continue on the current state.
			break;

		case GameState::QUIT:
			letsQuit = true;
			break;

		default:
			break;
		}

		// Printing everything on the screen.
		if (this->window)
		{
			this->window->clear();
			this->currentState->render();
			this->window->refresh();
		}

		// Let's wait a bit if the framerate is too low.
		this->window->delayFramerateIfNeeded();
	}
}

