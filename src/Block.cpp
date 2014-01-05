#include "Block.hpp"

Block::Block(Window* window, float x, float y, Color color, BlockType type):
	FallingObject(x, y, BLOCK_WIDTH, BLOCK_HEIGHT),
	DamageableObject(100),
	window(window),
	color(color),
	type(type)
{

}
Block::~Block()
{

}
void Block::update(float dt)
{
	this->preUpdate(dt);

	this->desiredPosition->addX(this->vx);
	this->desiredPosition->addY(this->vy);
}

void Block::render(float cameraX, float cameraY)
{
	this->window->drawBox(this->box, this->color);
}

