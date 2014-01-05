#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include <vector>
#include "GameObject.hpp"
#include "DamageableObject.hpp"
#include "Animation.hpp"
#include "SFX.hpp"
#include "Window.hpp"

/// User-controllable character.
///
class Player: public GameObject,
              public DamageableObject
{
public:
	enum FacingDirection { LEFT, RIGHT };
	enum PossibleAnimation
	{
		JUMPING_LEFT=0, JUMPING_RIGHT,
		FALLING_LEFT,   FALLING_RIGHT,
		STANDING_LEFT,  STANDING_RIGHT,
		RUNNING_LEFT,   RUNNING_RIGHT,
		DASHING_LEFT,   DASHING_RIGHT,
		DAMAGING_LEFT,  DAMAGING_RIGHT,
		DEATH_LEFT,     DEATH_RIGHT,

		ANIMATION_MAX // This arbitrary value exists so the
		              // animation vector can be safely resized
		              // to contain all possible animations
	};

	Player(Window* window, float x, float y, int w, int h, int hp, float acceleration);
	virtual ~Player();

	/// Updates everything and _tries_ to move.
	///
	/// @note Must call *commitMovement()* to allow it to move.
	///
	void update(float dt);

	/// Shows onscreen.
	void render(float cameraX=0, float cameraY=0);

	/// Respond to any input commands.
	void updateInput();

	/// Updates internal animation status.
	void updateAnimation();

	/// _Actually_ moves the player.
	void commitMovement();

	void setHorizontalLimit(int left, int right);
	void setVerticalLimit(int top, int bottom);

	/// Makes the player jump or stops it in mid-air.
	///
	/// @note If you send `jump(false)` it will stop the
	///       player completely (on the y axis).
	///
	void jump(bool willJump=true);

	/// Forces the player to suffer gravity.
	void fall();

	/// Tells if the player's dead.
	bool isHittable();
	bool Dashing();
	bool isFalling();
	bool Winned();

	/// Makes the player die.
	void die();
	bool died();

	void dealDamage();

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

private:
	/// Window on which the player is shown.
	Window* window;

	float vx; ///< Speed component of the x axis.
	float vy; ///< Speed component of the y axis.
	float ax; ///< Current acceleration on the x axis.
	float ay; ///< Current acceleration on the y axis.

	/// How much speed the player wants to have on the
	/// current frame.
	float targetVx;

	/// Walking speed
	float acceleration;

	/// How much of the speed we consider the player stopped.
	float stoppedThreshold;

	Animation* currentAnimation;

	/// All possible animations, ready to be selected.
	std::vector<Animation*> animations;

	FacingDirection facingDirection;

	/// Tells if the player's limited on the X axis.
	bool hasHorizontalLimit;
	int rightmostLimitX;
	int leftmostLimitX;

	/// Tells if the player's limited on the Y axis.
	bool hasVerticalLimit;
	int topLimitY;
	int bottomLimitY;

	/// Is it on air (due to jumping or falling).
	bool inAir;

	/// Is it currently jumping for the first time.
	bool isJumping;

	/// Is it currently jumping for the second time.
	bool isDoubleJumping;

	/// If player already reach the end of the game AND wins
	bool win;

	/// Ammount of strength the player has when jumping.
	///
	/// Force applied to itself when jumping.
	float thrust;

	bool damaging;  ///< Is it currently having damage.

	// /// The movable platform that the player's currently on top.
	// ///
	// /// This should point to the current movable platform.
	// /// It will make the player move along with it.
	// ///
	// /// If there is no movable platform (this is NULL), the
	// /// player will behave normally.
	// PlatformMovable* movablePlatform;

	SFX* jumpSFX;
};

#endif //PLAYER_H_DEFINED

