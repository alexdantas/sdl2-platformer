#include "SDL.hpp"
#include "Log.hpp"

bool SDL::init()
{
	// Will initialize subsystems separatedly

	if (SDL_Init(0) < 0)
	{
		Log::error("SDL_Init: Couldn't start SDL");
		Log::error(std::string(SDL_GetError()));
		throw "SDL Init Fail";
	}

	// Initializing everything related to AUDIO

	if (SDL_WasInit(SDL_INIT_AUDIO) != 0)
	{
		Log::error("SDL_WasInit: Tried to reinitailize Audio");
		Log::error(SDL_GetError());
		throw "SDL_WasInit Fail";
	}
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		Log::error("SDL_Init: Couldn't start Audio");
		Log::error(std::string(SDL_GetError()));
		throw "SDL_Init Fail";
	}

	int flags = MIX_INIT_OGG | MIX_INIT_MP3;
	if ((Mix_Init(flags) & flags) != flags)
	{
		Log::warning("Mix_Init: Couldn't start Audio");
		Log::warning(Mix_GetError());
	}

	// TODO: How do I find out the optimal
	//       audio rate of a music?

	if (-1 == Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, // audio rate
	                        MIX_DEFAULT_FORMAT,    // format
	                        2,                     // channels
	                        4096))                 // buffers
	{
		Log::warning("Mix_OpenAudio: Couldn't start Audio");
		Log::warning(Mix_GetError());
	}

	// Reserving 16 channels (meaning 16 simultaneous SFXs playing)
	Mix_AllocateChannels(16);

	// Initializing everything related to VIDEO

	// Subtle bug here: If VIDEO is initialized but EVENTS
	//                  not or virce-versa.

	flags = (SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (SDL_WasInit(flags) != 0)
	{
		Log::error("SDL_WasInit: Tried to reinitailize Video");
		Log::error(std::string(SDL_GetError()));
		throw "SDL_WasInit Fail";
	}
	if (SDL_InitSubSystem(flags) < 0)
	{
		Log::error("SDL_Init: Couldn't start Video");
		Log::error(std::string(SDL_GetError()));
		throw "SDL_Init Fail";
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		Log::error("IMG_Init: Couldn't start PNG support");
		Log::error(std::string(IMG_GetError()));
		throw "IMG_Init Fail";
	}
	if (TTF_Init() == -1)
	{
		Log::error("TTF_Init: Couldn't start TTF support");
		Log::error(std::string(TTF_GetError()));
		throw "TTF_Init Fail";
	}

	return true;
}
void SDL::exit()
{
	// Freeing everything related to VIDEO


	// Freeing everything related to AUDIO


	Mix_AllocateChannels(0); // Frees all allocated channels

	//Mix_Quit(); segmentation fault! why?
	Mix_CloseAudio();

	// Freeing everything related to FONTS

	if (TTF_WasInit())
		TTF_Quit();

	SDL_Quit();
}

