#ifndef SFX_H_DEFINED
#define SFX_H_DEFINED

#include <vector>
#include "SDL.hpp"

/// Sound effects for the win!
///
/// This class supports WAVE, RIFF, AIFF, OGG and VOC file types.
///
class SFX
{
public:
	/// Initializes pretty much everything.
	/// Yeah, don't bother calling any of the functions below unless
	/// you want to override the SFX filepath.
	SFX(std::string filepath);

	virtual ~SFX();

	/// Plays the loaded SFX once (or `times`).
	///
	/// @param times How many times we'll play the SFX.
	///              If -1, infinite loop.
	///
	/// @note If called multiple times, will wait for it to
	///       finish before playing again.
	///
	bool play(int times=1);

	/// Pauses this sound effect.
	void pause();

	/// Unpauses this sound effect.
	void unpause();

	/// Stops this sound effect.
	void stop();

	/// Tells if this sound effect is currently playing.
	bool isPlaying();

	/// Tells if this sound effect is currently paused.
	bool isPaused();

	/// Returns the current volume of this sound effect.
	int getVolume();

	/// Sets the volume of this sound effect to `volume`.
	///
	/// @return The previous value.
	///
	int setVolume(int volume);

	// These methods affect all loaded sound effects

	/// Returns the maximum volume allowed for sound effects.
	///
	/// @note Minimum is always zero.
	///
	static int getMaxVolume();

	/// Sets the volume of all SFXs to `volume`.
	///
	/// @return The previous value.
	///
	static int setVolumeAll(int volume);

	/// Stops all currently-playing sound effects.
	static void stopAll();

	/// Pauses all currently-playing sound effects.
	static void pauseAll();

	/// Resumes all currently-paused sound effects.
	static void unpauseAll();

private:

    /// Internal SDL2_mixer's data structure that handles sfx.
	Mix_Chunk* sfx;

    /// The file path of the currently loaded sound effect.
	std::string filepath;

	/// The current channel where this SFX is playing.
	int channel;

	/// Contains all SFXs created up until now.
	///
	/// This exists so when setting the volume on one SFX will
	/// affect all of them.
	static std::vector<SFX*> all;
};

#endif /* SFX_H_DEFINED */
