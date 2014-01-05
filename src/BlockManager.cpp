#include "BlockManager.hpp"
#include "Utils.hpp"

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
		blocks[i]->update(dt);
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

