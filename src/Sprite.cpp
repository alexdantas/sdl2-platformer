#include "Sprite.hpp"
#include "Log.hpp"

Sprite::Sprite(Window* window, std::string filename):
	window(window),
	filename(filename),
	image(nullptr),
	clipRect(nullptr),
	width(0),
	height(0)
{
	this->image = window->loadImage(this->filename);
	if (!(this->image))
	{
		Log::error("Sprite::load Failed on '" +
		           this->filename +
		           "'");
	}
	else
	{
		Log::debug("Sprite::load: '" +
		           this->filename +
		           "'");

		// Will query the image's attributes
		int w, h;
		SDL_QueryTexture(image, nullptr, nullptr, &w, &h);

		this->width  = w;
		this->height = h;

		// Will print image at it's original size
		this->crop(Rectangle(0, 0, this->width, this->height));
	}
}
Sprite::~Sprite()
{
	if (this->image)
		this->window->freeImage(this->image);

	if (this->clipRect)
		delete this->clipRect;
}
void Sprite::crop(Rectangle rect)
{
    if (!(this->clipRect))
	    this->clipRect = new Rectangle;

    this->clipRect->copy(&rect);
}
void Sprite::render(int x, int y)
{
	Rectangle destination(x, y, this->clipRect->w, this->clipRect->h);

	this->window->renderImage(this->image,
	                          this->clipRect,
	                          &destination);
}
// void Sprite::setTransparentRGBColor(Color color)
// {
//     Uint32 colorKey =
//SDL_MapRGB(this->surface->format,
//
//color.r(), color.g(), color.b());

//     SDL_SetColorKey(this->surface, SDL_SRCCOLORKEY, colorKey);
// }
int Sprite::getWidth()
{
	return this->clipRect->w;
}
int Sprite::getHeight()
{
	return this->clipRect->h;
}
void Sprite::restore()
{
	this->crop(Rectangle(0, 0, this->width, this->height));
}

