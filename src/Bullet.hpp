#ifndef BULLET_H_DEFINED
#define BULLET_H_DEFINED

#include "FallingObject.hpp"
#include "DamageableObject.hpp"
#include "Window.hpp"
#include "Color.hpp"
#include "Shapes.hpp"

#define BULLET_WIDTH  5
#define BULLET_HEIGHT 5
#define BULLET_SPEED  5
#define BULLET_COLOR  Color(255, 0, 0)

enum Direction
{
	FLY_LEFT, FLY_RIGHT
};

/// A single bullet
class Bullet: public GameObject
{
	// Let the BulletManager modify internal things
	friend class BulletManager;

public:
	Bullet(Window* window, float x, float y, Direction direction);

	virtual ~Bullet();

	void update(float dt);
	void render(float cameraX=0, float cameraY=0);

private:
	Window* window;
	Direction currentDirection;
	float speedX;
};

#endif //BULLET_H_DEFINED

