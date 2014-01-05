#include "Window.hpp"
#include "Log.hpp"
#include "Config.hpp"

Window::Window(uint32_t width, uint32_t height, std::string title):
	window(nullptr),
	surface(nullptr),
	renderer(nullptr),
	width(width),
	height(height),
	originalWidth(width),
	originalHeight(height),
	isFullscreen(false),
	title(title),
	bg_color(0, 0, 0),
	framerate(60),
	frame_delay(0),
	current_frame_delta(0)
{
    // Calling for the first time CREATES a window.
    // Storing it on this->window
    this->resize(title, width, height);


    if (!(this->window) || !(this->renderer) || !(this->surface))
    {
        Log::error("Window(): Couldn't create Window");
        throw "Window() Fail";
    }
    this->maximize();

    this->framerateTimer.start();

    this->clear();
    this->refresh();
	SDL_Delay(500);
}
Window::~Window()
{
	this->destroy();
}
void Window::resize(std::string title, unsigned int width, unsigned int height)
{
	// Just in case we already have a window
	this->destroy();

	// Taken from the Migration Guide
	// (http://wiki.libsdl.org/MigrationGuide)
	//
	// It creates a nice window independent of the user's
	// monitor size.
	SDL_CreateWindowAndRenderer(0,
	                            0,
	                            SDL_WINDOW_FULLSCREEN_DESKTOP,
	                            &(this->window),
	                            &(this->renderer));

	if (!(this->window) || !(this->renderer))
	{
		Log::error("Window::resize: Couldn't create SDL_Window or SDL_Renderer");
		return;
    }

    // And here we fake a "logical" size of the window,
    // independent of it's real size.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(this->renderer, width, height);

    // Lil' title
    this->setTitle(title);

    this->surface  = SDL_GetWindowSurface(this->window);
    if (!(this->surface))
	    return;

    this->width  = width;
    this->height = height;
}
void Window::destroy()
{
	if (this->renderer)
	{
		SDL_DestroyRenderer(this->renderer);
		this->renderer = nullptr;
	}

	if (this->window)
	{
		SDL_DestroyWindow(this->window);
		this->window = nullptr;
	}
}
void Window::refresh()
{
	SDL_RenderPresent(this->renderer);
}
SDL_Texture* Window::loadImage(std::string filename)
{
	SDL_Texture* texture = IMG_LoadTexture(this->renderer,
	                                       filename.c_str());
    if (!texture)
    {
	    Log::error("IMG_LoadTexture: Couldn't open image '" +
	               filename +
	               "': " +
	               IMG_GetError());
    }
    return texture;
}
void Window::freeImage(SDL_Texture* image)
{
	if (image)
		SDL_DestroyTexture(image);
}
void Window::freeImage(SDL_Surface* image)
{
	if (image)
		SDL_FreeSurface(image);
}
void Window::renderImage(SDL_Texture* texture, Rectangle* source, Rectangle* destination)
{
	if (!texture || !source || !destination)
	{
		Log::warning("Window::render: Tried to show a nullptr image");
		return;
	}

	SDL_Rect sdl_source = {
		(int)source->x, (int)source->y,
		source->w, source->h
	};
	SDL_Rect sdl_destination = {
		(int)destination->x, (int)destination->y,
		destination->w, destination->h
	};

    SDL_RenderCopy(this->renderer,
                   texture,
                   &sdl_source,
                   &sdl_destination);
}
bool Window::toggleFullscreen()
{
	// // SEE HERE
	// // http://boxplorer2.googlecode.com/svn/trunk/sdl2-test.cc

	// // Previous window position
	// int last_x;
	// int last_y;

	// if (!(this->isFullscreen))
	// {
	// 	// Capture current window position.
	// 	SDL_GetWindowPosition(this->window, &last_x, &last_y);
	// }

	// this->destroy();

	// if (!(this->isFullscreen))
	// {
	// 	this->window = SDL_CreateWindow(this->title,
	// 	                                  rect_[d].x, rect_[d].y,
	// 	                                  rect_[d].w, rect_[d].h,
	// 	                                  SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);

	// 	width_ = rect_[d].w;

	// 	height_ = rect_[d].h;

	// }
	// else
	// {
	// 	this->window = SDL_CreateWindow(this->title,
	// 	                                  last_x, last_y,
	// 	                                  last_width_, last_height_,
	// 	                           SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	// 	this->width  = last_width;
	// 	this->height = last_height;
	// }

	// this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	// this->isFullscreen = !(this->isFullscreen);
    return true;
}
void Window::minimize()
{
	SDL_MinimizeWindow(this->window);
}
void Window::maximize()
{
	SDL_MaximizeWindow(this->window);
}
void Window::restore()
{
	SDL_RestoreWindow(this->window);
}
void Window::fill(Color color)
{
	SDL_SetRenderDrawColor(this->renderer,
	                       color.r(),
	                       color.g(),
	                       color.b(),
	                       color.a());

	SDL_RenderClear(this->renderer);
}
void Window::clear()
{
	this->fill(this->bg_color);
}
void Window::setTitle(std::string title)
{
	if (this->window)
		SDL_SetWindowTitle(this->window, title.c_str());
}

void Window::setBackgroundColor(Color color)
{
	bg_color = color;
}
void Window::delayFramerateIfNeeded()
{
    this->current_frame_delta = this->framerateTimer.delta();

    if ((this->current_frame_delta) < (this->frame_delay))
	    SDL_Delay((this->frame_delay) - this->current_frame_delta);

    this->framerateTimer.restart();
}
unsigned int Window::getDelta()
{
	return this->current_frame_delta;
}

