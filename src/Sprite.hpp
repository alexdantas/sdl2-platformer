#ifndef SPRITE_H_DEFINED
#define SPRITE_H_DEFINED

#include <iostream>
#include "SDL.hpp"
#include "Color.hpp"
#include "Window.hpp"

/// Shows a single image onscreen.
///
/// This class opens an image and can be used to print it completely
/// or just a part of it.
///
/// For example, on the class *Animation*, we'll deal with opening a
/// large image and selectively printing parts of it.
///
/// ## How to use:
///
///     Sprite sprite("path/to/image.png");
///         /// on a loop...
///         sprite.render(50, 50);
///
/// Keep in mind you should refresh the screen to see any changes.
///
class Sprite
{
public:
	/// Creates and loads a new sprite from `filename` on `window`.
	Sprite(Window* window, std::string filename);

	virtual ~Sprite();

	/// Crops image according to `rect`.
	void crop(Rectangle rect);

	/// Places the sprite on `x` and `y` of it's `window`.
	///
	/// @note Don't forget to refresh the `Window`.
	///
	virtual void render(int x, int y);

	// /// Sets a RGB color on this sprite as transparent.
	// //	This means when printing this image, this color will be
	// //	passed-through and look invisible.
	// void setTransparentRGBColor(Color color=Color(255, 0, 255));

	/// Returns the width of the sprite image on pixels.
	int getWidth();

	/// Returns the height of the sprite image on pixels.
	int getHeight();

	void restore();

	void clip(int x, int y, int w, int h);

protected:
	/// The window on which this Sprite appears.
	///
	/// @note The only reason I need this here is
	///       because SDL needs a SDL_Window to create
	///       a SDL_Texture.
	///       If it ever changes, please remove this.
	///
	Window* window;

	/// Current image's filename.
	///
	///	Can be changed with setFilename().
	///	Remember to load() it after.
	std::string filename;

	/// SDL's internal thingy that holds the image data.
	SDL_Texture* image;

	/// In case we apply some sort of rotation or zoom on the
	/// original surface, this is where it'll be saved.
	SDL_Surface* surfaceRotoZoom;

	/// Which part of the image is printed onscreen.
	//
	//	Normally it's the whole image, but you can clip()
	//	it if you like.
	Rectangle* clipRect;

	/// If we've rotoZoomed the image, this is the clip we're
	/// using to print it onscreen.
	SDL_Rect rotoZoomClipRect;

	float angle;
	float scaleX;
	float scaleY;

	int width;
	int height;
};

#endif /* SPRITE_H_DEFINED */
