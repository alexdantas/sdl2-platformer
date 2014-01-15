#include "Bullet.hpp"

Bullet::Bullet(Window* window, float x, float y, Direction direction):
	GameObject(x, y, BULLET_WIDTH, BULLET_HEIGHT),
	window(window),
	currentDirection(direction),
	speedX(BULLET_SPEED)
{ }
Bullet::~Bullet()
{

}
void Bullet::update(float dt)
{
	this->box->addX(this->speedX);
}
void Bullet::render(float cameraX, float cameraY)
{
	this->window->drawBox(this->box, BULLET_COLOR);
}

