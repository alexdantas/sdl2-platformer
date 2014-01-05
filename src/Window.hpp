#ifndef WINDOW_H_DEFINED
#define WINDOW_H_DEFINED

#include <string>
#include "SDL.hpp"
#include "Color.hpp"
#include "Shapes.hpp"
#include "Timer.hpp"

/// The main (and only) window of the program.
///
/// Wraps low-level SDL video functions that interfaces with the
/// Operational System's Window Manager.
///
/// Here we set things like fullscreen, window position, size, etc.
///
/// @note Most of these functions may fail horribly depending
///       on the OS! Do not rely on them too much.
///       The ones that may fail have their descriptions started
///       with _Tries to_.
///
/// ## For developers
///
/// This class also deals with framerates and frame delay.
/// Here's an explanation on how it does it:
///
/// The FPS on a powerful machine is fast and the FPS is slow
/// on a poor computer.
///
/// If on our code we have a movement like this:
///
///     Player.x += 1;
///
/// Then it will move 30 pixels per second on a machine with
/// 30 FPS and 60 pixels per second on a machine with 60 FPS
/// (slow and fast machines, respectivelly).
///
/// Now if we have a movement like this:
///
///     Player.x += 45 * dt;
///
/// Then the player will move 45 pixels per second INDEPENDENT
/// of the machine's FPS.
///
/// That's because if *dt* is the ammount of seconds since last
/// frame, if we keep doing this every frame:
///
///     float var += 1 * dt;
///
/// Then after 1 second the variable will have 1 INDEPENDENT
/// of the machine's FPS.
///
/// THAT's what those `frame_*` variables at
/// the end of `Window` does.
///
class Window
{
public:
	/// Initializes the program's window with *width*, *height*
	/// and the text that should appear on the program's window
	/// (*title*).
	Window(unsigned int width, unsigned int height, std::string title="");

	virtual ~Window();

	/// Destroys everything on the window and itself.
	/// Can be recreated with `Window::resize`.
	void destroy();

	void renderImage(SDL_Texture* texture, Rectangle* source, Rectangle* destination);

	SDL_Texture* loadImage(std::string filename);

	void freeImage(SDL_Texture* image);
	void freeImage(SDL_Surface* image);

	/// Effectively draws everything that's onscreen.
	/// @note Need to be called constantly.
	void refresh();

	/// Toggles fullscreen mode of the program's window.
	bool toggleFullscreen();

	/// Hides the window.
	void minimize();

	/// Makes the window as big as possible without going fullscreen.
	void maximize();

	/// Restores original size of a Minimized or Maximized window.
	void restore();

	/// Set Window icon to *filepath*.
	///
	/// @note Win32 icons must be 32x32.
	void setIcon(std::string filepath);

	/// Resizes the program's window to `width`/`height` with `title`.
	void resize(std::string title, unsigned int width, unsigned int height);

	/// Tries to center the program's window position onscreen.
	void center();

	/// Tries to set the program's window position to *x*/*y*.
	void move(int x, int y);

	/// Fills the whole Window with `color`.
	void fill(Color color);

	/// Clears whole window to the background color #bg_color.
	void clear();

	/// Sets the background color to a RGB-formatted color.
	///
	/// @note Affects clearScreen().
	void setBackgroundColor(Color color=Color(0, 0, 0));

	void setTitle(std::string title);

	// Those are public but you SHOULDN'T change them!
	// They're here for ease of access (Window::width insteadj
	// of Window::getWidth(), and such).

	/// SDL's internal data structure that represents the window.
	SDL_Window* window;

	/// SDL's internal data structure that represents the surface
	/// contained by the window.
	SDL_Surface* surface;

	SDL_Renderer* renderer;

	unsigned int width;  ///< Current window width.
	unsigned int height; ///< Current window height.

	/// Original window height (the height game developers had in mind
	/// when making this game).
	///
	/// In other words, the optimal width for the game.
	unsigned int originalWidth;

	/// Original window height (the height game developers had in mind
	/// when making this game).
	///
	/// In other words, the optimal height for the game.
	unsigned int originalHeight;

	/// Tells if the window is currently fullscreen.
	bool isFullscreen;

	/// Waits as long as needed to keep the framerate.
	///
	/// When we start `Window` we define an ideal framerate.
	/// Let's say it's 30.
	///
	/// Then, the `framerate_delay` (or, how much time
	/// each frame should ideally take) is 1(second)/30(frames).
	///
	/// So inside each `Window` we have a `Timer` that
	/// counts how many milliseconds the last frame took.
	///
	/// If that time is less than the ideal `framerate_delay`,
	/// we'll wait until it is equal to it.
	///
	/// If the time is greater than the ideal delay, we
	/// go right through, expecting the next frame to take
	/// less.
	///
	/// If not, it will skip frames. Anyway, that's the best
	/// solution I could come up in such short time.
	///
	/// @note This function may not sleep at all.
	///
	void delayFramerateIfNeeded();

	/// Returns how may milliseconds have passed since
	/// the last frame and the current.
	///
	unsigned int getDelta();

private:
	/// Window caption (text that shows on the operational
	/// system's window).
	std::string title;

	/// The background color of the window.
	/// @note Changeable only by setBackgroundColor().
	Color bg_color;

	/// Timer responsible to get how much milliseconds
	/// have passed between last frame and the current.
	///
	/// * Based on this timer we fill `current_frame_delta`.
	/// * If it's small than `frame_delay` we'll sleep.
	/// * If it's greater, we'll skip right away.
	/// * `frame_delay` is based on `framerate`.
	///
	Timer framerateTimer;

	/// How many frames per second we're running.
	unsigned int framerate;

	/// Time (in milliseconds) each frame must have.
	///
	/// If the actual delay passed is less than this,
	/// we'll wait.
	/// If the delay is greater, we'll skip right away.
	///
	unsigned int frame_delay;

	/// How much time have passed since
	/// last frame (in milliseconds).
	///
	unsigned int current_frame_delta;
};

#endif //WINDOW_H_DEFINED

