#include "BlockManager.hpp"
#include "Utils.hpp"
#include <algorithm>
BlockManager::BlockManager(Window* window, unsigned int maxAmmount, Rectangle areaLimit):
	window(window),
	maxAmmount(maxAmmount),
	areaLimit(areaLimit)
{

}
BlockManager::~BlockManager()
{
	for (unsigned int i = 0; i < blocks.size(); i++)
		delete blocks[i];
}
void BlockManager::update(float dt)
{
	for (unsigned int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->update(dt);

		switch (blocks[i]->boundaryStatus)
		{
		case OFF_LEFT:
		case OFF_RIGHT:
			blocks[i]->vx = 0;
			break;

		case OFF_TOP:
		case OFF_BOTTOM:
			blocks[i]->vy = 0;
			break;

		default:
			break;
		}
	}

	// Checking collision between them, pair by pair
	std::vector<std::pair<int, int>> checked;

	for (unsigned int i = 0; i < blocks.size(); i++)
		for (unsigned int j = 0; j < blocks.size(); j++)

			if ((i != j) &&
			    (blocks[i]->collidedWith(blocks[j])) &&

			    // Since we're cross-checking every block,
			    // let's stop the one that's falling faster
			    (blocks[i]->vy > blocks[j]->vy))
			{
				// If a block collided with another,
				// put it on top of it and set it's speed
				// as the same as the other.
				blocks[i]->desiredPosition->placeOnTop(blocks[j]->box);

				blocks[i]->vy = blocks[j]->vy;
			}

	for (unsigned int i = 0; i < blocks.size(); i++)
		blocks[i]->commitMovement();
}
void BlockManager::render(float cameraX, float cameraY)
{
	for (unsigned int i = 0; i < blocks.size(); i++)
		blocks[i]->render(cameraX, cameraY);
}
void BlockManager::add(float x, float y, Color color, BlockType type)
{
	Block* block = new Block(this->window, x, y, color, type);

	block->setBoundary(this->areaLimit);
	this->blocks.push_back(block);
}
void BlockManager::addRandom()
{
	Color randomColor;
	randomColor.randomize();

	this->add(Utils::Random::between(this->areaLimit.leftmost,
	                                 this->areaLimit.rightmost),
	          Utils::Random::between(this->areaLimit.top,
	                                 this->areaLimit.bottom),
	          randomColor);
}
unsigned int BlockManager::currentAmmount()
{
	return this->blocks.size();
}

