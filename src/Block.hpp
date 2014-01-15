#ifndef BLOCK_H_DEFINED
#define BLOCK_H_DEFINED

#include "FallingObject.hpp"
#include "DamageableObject.hpp"
#include "Window.hpp"
#include "Color.hpp"
#include "Shapes.hpp"

#define BLOCK_WIDTH  90
#define BLOCK_HEIGHT 32

enum BlockType
{
	REGULAR, EXLODING
};

/// A single block
class Block: public FallingObject,
             public DamageableObject
{
	// Let the BlockManager modify internal vy
	friend class BlockManager;

public:
	Block(Window* window, float x, float y, Color color, BlockType type=REGULAR);

	virtual ~Block();

	void update(float dt);
	void render(float cameraX=0, float cameraY=0);

private:
	Window* window;
	Color color;
	BlockType type;
};

#endif //BLOCK_H_DEFINED

