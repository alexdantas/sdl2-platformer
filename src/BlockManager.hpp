#ifndef BLOCKMANAGER_H_DEFINED
#define BLOCKMANAGER_H_DEFINED

#include <vector>
#include "Block.hpp"
#include "Shapes.hpp"
#include "Window.hpp"
#include "Color.hpp"

///
class BlockManager
{
public:
	BlockManager(Window* window, unsigned int maxAmmount, Rectangle areaLimit);
	virtual ~BlockManager();

    /// Updates all the blocks inside it.
    void update(float dt);

    /// Renders all the blocks inside it.
    void render(float cameraX=0, float cameraY=0);

	/// Spawns a block at `x` `y`.
	void add(float x, float y, Color color, BlockType type=REGULAR);

    /// Adds a block at random inside the delimited area.
	void addRandom();

	unsigned int currentAmmount();

	std::vector<Block*> blocks;

private:
	Window* window;

	int maxAmmount;

	Rectangle areaLimit;


};

#endif //BLOCKMANAGER_H_DEFINED

