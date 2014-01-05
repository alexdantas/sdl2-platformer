#ifndef SDL_H_DEFINED
#define SDL_H_DEFINED

// SDL 2.0, beibeh
#include <SDL2/SDL.h>            // SDL2
#include <SDL2/SDL_video.h>      // SDL2
#include <SDL2/SDL_image.h>      // SDL2_Image
#include <SDL2/SDL_ttf.h>        // SDL2_TTF
#include <SDL2/SDL_mixer.h>      // SDL2_Mixer
#include <SDL2/SDL2_rotozoom.h>  // SDL2_GFX

//#include "Timer.hpp"
#include "Color.hpp"
#include "Shapes.hpp"

// Shuts up the compiler about unused parameters.
#define UNUSED(x) ((void)(x))

/// Wrapper on basic SDL2 calls.
///
/// This simply initializes and finishes SDL2.
///
/// Other classes too have direct SDL calls,
/// check out `Music` and `Window`.
///
namespace SDL
{
	/// Starts SDL2, MUST be called before everything else.
	bool init();

	/// Destroys SDL2, MUST be called when program ends.
	void exit();
};

#endif /* SDL_H_DEFINED */
