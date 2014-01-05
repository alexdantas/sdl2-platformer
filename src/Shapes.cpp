#include "Shapes.hpp"
#include <cstdlib> // abs()

Point::Point(float x, float y):
	x(x),
	y(y)
{ }

Point::Point():
	x(0),
	y(0)
{ }


Rectangle::Rectangle(float x, float y, int w, int h):
	x(x),
	y(y),
	w(w),
	h(h)
{
	this->update();
}
Rectangle::Rectangle():
	x(0),
	y(0),
	w(1),
	h(1)
{
	this->update();
}
Rectangle::Rectangle(Rectangle* other)
{
	this->copy(other);
}
void Rectangle::copy(Rectangle* other)
{
	this->x = other->x;
	this->y = other->y;
	this->w = other->w;
	this->h = other->h;

	this->update();
}
void Rectangle::addX(float x)
{
	this->x += x;

	this->update();
}
void Rectangle::addY(float y)
{
	this->y += y;

	this->update();
}
void Rectangle::setX(float x)
{
	this->x = x;

	this->update();
}
void Rectangle::setY(float y)
{
	this->y = y;

	this->update();
}
void Rectangle::stretch(float scale)
{
	this->stretch(scale, scale);
}
void Rectangle::stretch(float scaleX, float scaleY)
{
	if ((scaleX <= 0) || (scaleY <= 0)) return;

	float oldW = this->w;
	float oldH = this->h;

	this->w *= scaleX;
	this->h *= scaleY;

	// Centralizing one rectangle on the other
	this->x += abs(oldW - this->w)/2;
	this->y += abs(oldH - this->h)/2;

	this->update();
}
void Rectangle::update()
{
	this->top    = y;
	this->bottom = y + h;

	this->leftmost  = x;
	this->rightmost = x + w;

	this->center = Point(x + (w/2),
	                     y + (h/2));

	this->topLeft     = Point(x,     y);
	this->topRight    = Point(x + w, y);
	this->bottomLeft  = Point(x,     y + h);
	this->bottomRight = Point(x + w, y + h);

	this->topCenter    = Point(center.x,  top);
	this->bottomCenter = Point(center.x,  bottom);
	this->leftCenter   = Point(leftmost,  center.y);
	this->rightCenter  = Point(rightmost, center.y);
}
bool Rectangle::overlaps(Rectangle other)
{
	if ((      x <= other.rightmost) &&
	    (other.x <= rightmost)       &&
	    (      y <= other.bottom)    &&
	    (other.y <= bottom))
		return true;

	return false;
}
bool Rectangle::overlaps(Rectangle* other)
{
	if ((       x <= other->rightmost) &&
	    (other->x <= rightmost)        &&
	    (       y <= other->bottom)    &&
	    (other->y <= bottom))
		return true;

	return false;
}
void Rectangle::placeOnTop(Rectangle* other)
{
	this->y = (other->y - this->h);

	this->update();
}


Circle::Circle(float x, float y, int r):
	x(x),
	y(y),
	r(r)
{
	this->centerX = x + r;
	this->centerY = y + r;
}

void Circle::addX(float x)
{
	this->x       += x;
	this->centerX += x;
}

void Circle::addY(float y)
{
	this->y       += y;
	this->centerY += y;
}

