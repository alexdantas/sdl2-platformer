#ifndef BLOCKMANAGER_H_DEFINED
#define BLOCKMANAGER_H_DEFINED

#include <vector>
#include "Block.hpp"

///
class BlockManager
{
public:
	BlockManager(unsigned int maxAmmount, Rectangle areaLimit);
	virtual ~BlockManager();

    /// Updates all the blocks inside it.
    void update(float dt);

    /// Renders all the blocks inside it.
    void render(float cameraX=0, float cameraY=0);

	int currentAmmount();

private:
	int maxAmmount;

	std::vector<Block*>
};

#endif //BLOCKMANAGER_H_DEFINED

