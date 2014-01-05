#ifndef MUSIC_H_DEFINED
#define MUSIC_H_DEFINED

#include "SDL.hpp"

/// Loads and plays a music.
///
/// @note We can only have one music playing at the same time.
///
/// @note This class only works with OGG and MP3 formats,
///       but if you avoid calling `Music::setPosition()` then
///       it works with WAV, MOD and MIDI.
///
/// ## Usage
///
///     Music music("path/to/music.mp3");
///     music.play();
///
///     music.pause();
///
///     if (music.isPaused())
///         music.unpause();
///
///     music.stop();
///
/// ## For developers
///
/// This is a big wrapper over SDL2_Mixer calls.
///
/// One interesting thing is that SDL can be used for simple audio
/// management without necessarily interfering with graphics.
///
/// For instance, I've made a ncurses game
/// (full console, no graphics) with SDL audio.
///
class Music
{
public:

    /// Initializes everything and waits for a command.
    ///
    Music(std::string filepath);

    virtual ~Music();

    /// Plays the loaded music for `times` with optional
    /// `fadeInMs`.
    ///
    /// @param times How many times we'll play the music. If -1,
    ///              infinite loop.
    ///
    /// @param fadeInMs How many milliseconds for the fade-in
    ///                 effect to complete.
    ///
    /// @note Overwrites any other music that may be playing
    ///
	bool play(int times=-1, int fadeInMs=0);

	/// Starts fading out the currently playing song, lasting
	/// for `ms` milliseconds.
	///
	void fadeOut(int ms);

    /// Stops the music (along with all musics currently playing).
    ///
    /// The problem with SDL_Mixer's API is that when I tell it to
    /// stop playing music, it stops all musics currently playing.
    ///
    void stop();

    /// Pauses the music (along with all musics currently playing).
	void pause();

    /// Unpauses the music (along with all musics currently playing).
    void unpause();

    /// Starts playing the music from the beginning again.
    void restart();

	/// Rewinds the music to the start.
	///
	/// Works both on already-playing and paused songs.
	void rewind();

	/// Sets the position of the _playing_ music to `seconds`.
	///
	/// @note This function's the reason why this class
	///       only works with .OGG and .MP3 :(
	///       Meaning that if you avoid calling this,
	///       it might work with WAV, MOD and MIDI.
	///
	void setPosition(double seconds);

	/// Tells if the music is playing right now.
	bool isPlaying();

	/// Tells if the music is paused right now.
	bool isPaused();

	/// Tells if the music is fading in right now.
	bool isFadingIn();

	/// Tells if the music is fading out right now.
	bool isFadingOut();

	/// Set the music's volume to `volume`.
	///
	/// @see getMaxVolume()
	///
	/// @return The previous volume.
	int setVolume(int volume);

	/// Returns the current volume.
	int getVolume();

	/// Returns the maximum value allowed for the volume.
	///
	/// @note Minimum is always zero.
	///
	int getMaxVolume();

private:

    /// Internal SDL2_mixer's data structure that handles music.
    Mix_Music* music;

    /// The file path of the currently loaded music.
    std::string filepath;
};

#endif /* MUSIC_H_DEFINED */
