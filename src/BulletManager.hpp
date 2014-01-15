#ifndef BULLETMANAGER_H_DEFINED
#define BULLETMANAGER_H_DEFINED

#include <vector>
#include "Bullet.hpp"
#include "Shapes.hpp"
#include "Window.hpp"
#include "Color.hpp"

///
class BulletManager
{
public:
	BulletManager(Window* window, unsigned int maxAmmount, Rectangle areaLimit);
	virtual ~BulletManager();

    /// Updates all the bullets inside it.
    void update(float dt);

	void checkCollisions();

    /// Renders all the bullets inside it.
    void render(float cameraX=0, float cameraY=0);

	/// Spawns a bullet at `x` `y`.
	void add(float x, float y, Direction direction);

	unsigned int currentAmmount();

	std::vector<Bullet*> bullets;

private:
	Window* window;

	int maxAmmount;

	Rectangle areaLimit;
};

#endif //BULLETMANAGER_H_DEFINED

