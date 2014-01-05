#include "GameObject.hpp"

// Almost a purely virtual class

GameObject::GameObject(float x, float y, int w, int h):
    position(nullptr),
    box(nullptr)
{
    this->position = new Point(x, y);
    this->box      = new Rectangle(x, y, w, h);

}
GameObject::~GameObject()
{
	delete this->position;
	delete this->box;
}
float GameObject::getX()
{
    return this->box->x;
}
float GameObject::getY()
{
    return this->box->y;
}
float GameObject::getCenterX()
{
    return this->box->center.x;
}
float GameObject::getCenterY()
{
    return this->box->center.y;
}
int GameObject::getWidth()
{
    return this->box->w;
}
int GameObject::getHeight()
{
    return this->box->h;
}
bool GameObject::collidedWith(GameObject* other)
{
    return (this->box->overlaps(other->box));
}

