#include "BulletManager.hpp"
#include "Utils.hpp"
#include <algorithm>
BulletManager::BulletManager(Window* window, unsigned int maxAmmount, Rectangle areaLimit):
	window(window),
	maxAmmount(maxAmmount),
	areaLimit(areaLimit)
{ }
BulletManager::~BulletManager()
{
	for (unsigned int i = 0; i < bullets.size(); i++)
		delete bullets[i];
}
void BulletManager::update(float dt)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
		bullets[i]->update(dt);
}
void BulletManager::checkCollisions()
{
	// If they're outside their area
	for (std::vector<Bullet*>::iterator it = bullets.begin();
	     it != bullets.end();
	     ++it)
	{
		switch ((*it)->boundaryStatus)
		{
		case INSIDE_LIMITS:
			// Don't do shit
			break;

		default:
			// delete this bullet

			// std::swap(it, bullets.back());
			// bullets.pop_back();

			// --it;

			break;
		}
	}
}
void BulletManager::render(float cameraX, float cameraY)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
		bullets[i]->render(cameraX, cameraY);
}
void BulletManager::add(float x, float y, Direction direction)
{
	Bullet* bullet = new Bullet(this->window, x, y, direction);

	bullet->setBoundary(this->areaLimit);
	this->bullets.push_back(bullet);
}
unsigned int BulletManager::currentAmmount()
{
	return this->bullets.size();
}

