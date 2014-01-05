#ifndef FALLINGOBJECT_H_DEFINED
#define FALLINGOBJECT_H_DEFINED

#include "GameObject.hpp"

///
class FallingObject: public GameObject
{
public:
	FallingObject(float x, float y, int w, int h);
	virtual ~FallingObject();

	void preUpdate(float dt);

	/// _Actually_ moves the player.
	void commitMovement();

	/// Next position the player wants to be.
	///
	/// At each frame the player updates it's position on this
	/// *Rectangle*. Then, the *GameState* is responsible for
	/// allowing this or not.
	///
	/// It might now allow it because of collisions. Then the
	/// player will stay at it's current position.
	///
	Rectangle* desiredPosition;

protected:
	float vx; ///< Speed component of the x axis.
	float vy; ///< Speed component of the y axis.
	float ax; ///< Current acceleration on the x axis.
	float ay; ///< Current acceleration on the y axis.

	/// How much speed the player wants to have on the
	/// current frame.
	float targetVx;

	/// Is it on air (due to jumping or falling).
	bool inAir;
};

#endif //FALLINGOBJECT_H_DEFINED

