#include <cmath> // fabs()
#include "Player.hpp"
#include "InputManager.hpp"
#include "GameStateGame.hpp"
#include "Log.hpp"
#include "PhysicsManager.hpp"
#include "Config.hpp"
#include "Utils.hpp"

Player::Player(Window* window, float x, float y, int w, int h, int hp, float acceleration):
	GameObject(x, y, w, h),
	DamageableObject(hp),
	desiredPosition(NULL),
	window(window),
	vx(0), vy(0),
	ax(0), ay(0),
	acceleration(acceleration),
	stoppedThreshold(acceleration/5.5), // 10% of the speed
	currentAnimation(NULL),
	facingDirection(RIGHT),
	hasHorizontalLimit(false),
	hasVerticalLimit(false),
	inAir(false),
	isJumping(false),
	isDoubleJumping(false),
	win(false),
	thrust(Config::getInt("jump", 33)),
	damaging(false),
//	movablePlatform(NULL),
	jumpSFX(NULL)
{
	Animation* tmp = NULL;

	this->animations.resize(ANIMATION_MAX);

	int animationSpeed = Config::getInt("framerate", 30);

	tmp = new Animation(this->window, "images/lenny/standing.png", 1, animationSpeed);
	this->animations[STANDING_LEFT] = tmp;

	tmp = new Animation(this->window, "images/lenny/angry.png", 6, 2);
	this->animations[STANDING_RIGHT] = tmp;

	tmp = new Animation(this->window, "images/lenny/walking-left.png", 1, animationSpeed);
	this->animations[RUNNING_LEFT] = tmp;

	tmp = new Animation(this->window, "images/lenny/walking-right.png", 1, animationSpeed);
	this->animations[RUNNING_RIGHT] = tmp;

	tmp = new Animation(this->window, "images/lenny/walking-left.png", 1, animationSpeed);
	this->animations[JUMPING_LEFT] = tmp;

	tmp = new Animation(this->window, "images/lenny/walking-right.png", 1, animationSpeed);
	this->animations[JUMPING_RIGHT] = tmp;

	tmp = new Animation(this->window, "images/lenny/walking-left.png", 1, animationSpeed);
	this->animations[FALLING_LEFT] = tmp;

	tmp = new Animation(this->window, "images/lenny/walking-right.png", 1, animationSpeed);
	this->animations[FALLING_RIGHT] = tmp;

	tmp = new Animation(this->window, "images/lenny/standing.png", 1, animationSpeed, 1);
	this->animations[DAMAGING_LEFT] = tmp;

	tmp = new Animation(this->window, "images/lenny/standing.png", 1, animationSpeed, 1);
	this->animations[DAMAGING_RIGHT] = tmp;

	tmp = new Animation(this->window, "images/lenny/standing.png", 1, animationSpeed, 1);
	this->animations[DEATH_LEFT] = tmp;

	tmp = new Animation(this->window, "images/lenny/standing.png", 1, animationSpeed, 1);
	this->animations[DEATH_RIGHT] = tmp;

	// Let's start by looking at our right.
	this->currentAnimation = this->animations[STANDING_RIGHT];
	this->currentAnimation->start();

	this->desiredPosition = new Rectangle();

	this->jumpSFX = new SFX("sounds/sfx/jump.ogg");
}
Player::~Player()
{
	// TODO TODO BUG HACK OMG
	//
	// NEED TO DELETE ALL THINGS I'VE MALLOCED

}
void Player::update(float dt)
{
	this->desiredPosition->copy(this->box);

	// The acceleration is reseted each frame
	this->ay = 0;
	this->targetVx = 0;

	// These will define the resulting acceleration
	// (adding all the forces - input force, gravity force, etc)
	this->updateInput();

	// Player will ALWAYS suffer gravity.
	// The collision resolution scheme is resposible for not
	// letting the player go through stuff.
	this->vy += (PhysicsManager::gravityAcceleration * dt);

	// HORIZONTAL MOVEMENT
	// Acceleration rate: How fast the player hits the
	//                    full speed.
	//
	// 1: Instant Full-Speed
	// 0: Never Moves
	float a = 0.2612312321;

	// Method 1 of accelerating
	//
	// http://higherorderfun.com/blog/2012/05/20/the-guide-to-implementing-2d-platformers/
	this->vx = (a * this->targetVx) + ((1 - a) * this->vx) * dt;

	// Method 2 of accelerating
	//
	// http://earok.net/sections/articles/game-dev/theory/simplified-acceleration-games
	// this->vx += ((this->targetVx - this->vx) * a) * dt;

	// Making sure we will not be sliding indefinitely,
	// stopping if we hit a certain low speed.
	if (fabs(this->vx) < this->stoppedThreshold)
		this->vx = 0;

	if(this->damaging)
	{
		if(this->facingDirection == RIGHT)
			this->vx = -10;
		else
			this->vx = 10;
	}

	// deaccelerating for smoothness
	// this->vx *= PhysicsManager::groundFriction;
	// this->vy *= PhysicsManager::airFriction;

	// actually moving the pixels on the screen
	if (this->isAlive)
	{
		this->desiredPosition->addX(this->vx);
		this->desiredPosition->addY(this->vy);
	}

	// // Movable Platforms
	// //
	// // If the player's standing above one, we will move
	// // the player the same ammount as the platform moved
	// // on the last frame.
	// //
	// // This will remove completely "slippery movable platforms".
	// // If that's a feature to you, uncomment below.
	// if (this->movablePlatform)
	// {
	// 	PlatformMovable* p  = this->movablePlatform;
	// 	float platformDelta = (p->box->x - p->previousBox.x);

	// 	this->desiredPosition->addX(platformDelta);
	// }

	// Limiting, if necessary
	if (this->hasHorizontalLimit)
	{
		if (this->desiredPosition->x < this->leftmostLimitX)
			this->desiredPosition->x = this->leftmostLimitX;

		if ((this->desiredPosition->x + this->desiredPosition->w) > this->rightmostLimitX)
			this->desiredPosition->x = (this->rightmostLimitX - this->desiredPosition->w);

		this->desiredPosition->update();
	}

	if (this->hasVerticalLimit)
	{
		if (this->desiredPosition->y < this->topLimitY)
			this->desiredPosition->y = this->topLimitY;

		if ((this->desiredPosition->y + this->desiredPosition->h) >= this->bottomLimitY)
		{
			this->desiredPosition->y = (this->bottomLimitY - this->desiredPosition->h);

			// On this SPECIAL CASE, if the player hit the bottom
			// of the screen, will not jump anymore.
			this->jump(false);
		}

		this->desiredPosition->update();
	}

	// Updating visible
	if (this->isAlive)
		this->desiredPosition->update();

	this->updateAnimation();
}
void Player::render(float cameraX, float cameraY)
{
	this->currentAnimation->render(this->position->x - cameraX,
	                               this->position->y - cameraY);
}
void Player::updateInput()
{
	InputManager* input = InputManager::getInstance();

	float turbo = 1.7;

	if (this->damaging)
		return;

	if (input->isKeyPressed(KEY_A) ||
	    input->isKeyPressed(KEY_LEFT))
	{
		this->targetVx = (-1 * this->acceleration);
		this->facingDirection = LEFT;

		if (input->shift())
			this->targetVx *= turbo;
	}

	if (input->isKeyPressed(KEY_D) ||
	    input->isKeyPressed(KEY_RIGHT))
	{
		this->targetVx = (this->acceleration);
		this->facingDirection = RIGHT;

		if (input->shift())
			this->targetVx *= turbo;
	}

	if (input->isKeyDown(KEY_W)  ||
	    input->isKeyDown(KEY_UP) ||
	    input->isKeyPressed(KEY_Z))
	{
		this->jump();
		this->jumpSFX->play();
	}

	if (input->isKeyDown(KEY_DELETE))
	{
		this->die();
	}

	if (input->isKeyDown(KEY_BACKSPACE))
		this->dealDamage();


	if (input->isKeyDown(KEY_L))
		Log::log("Player: (" +
		         Utils::intToString(this->position->x) +
		         ", " +
		         Utils::intToString(this->position->y) +
		         ")");

	// TODO TMP TEMP
	if (input->isKeyDown(KEY_O))
		PhysicsManager::gravityAcceleration += 0.5;
	if (input->isKeyDown(KEY_I))
		PhysicsManager::gravityAcceleration -= 0.5;
}
void Player::updateAnimation()
{
	this->currentAnimation->update();

	// These will make transitions a lot easier
	bool willChangeAnimation = false;
	Animation* tmp = NULL;

	// I *know* this is fucking plain bad-coding,
	// but I haven't thought of a cleaner way of expressing this.
	//
	// I mean, there's a lot of animations and I must check
	// at each frame if it's going to change.
	//
	// And there's a whole tree of possible animations depending
	// on a lot of circumstances... Damn, dude.

	// The first thing we should worry about is whether he's alive
	if (!(this->isAlive))
	{
		if (this->facingDirection == RIGHT)
		{
			if (this->currentAnimation != this->animations[DEATH_RIGHT])
			{
				willChangeAnimation = true;
				tmp = this->animations[DEATH_RIGHT];
			}
		}
		else
		{
			if (this->currentAnimation != this->animations[DEATH_LEFT])
			{
				willChangeAnimation = true;
				tmp = this->animations[DEATH_LEFT];
			}
		}
	}
	// Then we see if he's taking tamage
	else if (this->damaging)
	{
		if (this->facingDirection == RIGHT)
		{
			if (this->currentAnimation != this->animations[DAMAGING_RIGHT])
			{
				willChangeAnimation = true;
				tmp = this->animations[DAMAGING_RIGHT];
			}
		}
		else
		{
			if (this->currentAnimation != this->animations[DAMAGING_LEFT])
			{
				willChangeAnimation = true;
				tmp = this->animations[DAMAGING_LEFT];
			}
		}

		if (!(this->currentAnimation->isRunning()))
		{
			this->damaging = false;
			this->currentAnimation->start();
		}
	}
	// Finally, the other cases (NOT dead AND not hurt)
	else
	{
		if (this->inAir)
		{
			if (this->facingDirection == RIGHT)
			{
				if(!this->isFalling()) //He is the air and is jumping
				{
					if (this->currentAnimation != this->animations[JUMPING_RIGHT])
					{
						willChangeAnimation = true;
						tmp = this->animations[JUMPING_RIGHT];
					}
					if(this->isDoubleJumping) //Jump again!
						this->currentAnimation->start();
				}
				else //Suffers the gravity
				{
					if (this->currentAnimation != this->animations[FALLING_RIGHT])
					{
						willChangeAnimation = true;
						tmp = this->animations[FALLING_RIGHT];
					}
				}

			}
			else // facingDirection == LEFT
			{
				if(!this->isFalling()) //He is the air and is jumping
				{
					if (this->currentAnimation != this->animations[JUMPING_LEFT])
					{
						willChangeAnimation = true;
						tmp = this->animations[JUMPING_LEFT];
					}
					if(this->isDoubleJumping) //Jump again!
						this->currentAnimation->start();
				}
				else //Suffers the gravity
				{
					if (this->currentAnimation != this->animations[FALLING_LEFT])
					{
						willChangeAnimation = true;
						tmp = this->animations[FALLING_LEFT];
					}
				}
			}
		}
		else // is not jumping
		{
			if (fabs(this->vx) < this->stoppedThreshold) // it is stopped
			{
				if (this->facingDirection == RIGHT)
				{
					if (this->currentAnimation != this->animations[STANDING_RIGHT])
					{
						willChangeAnimation = true;
						tmp = this->animations[STANDING_RIGHT];
					}
				}
				else // facingDirection == LEFT
				{
					if (this->currentAnimation != this->animations[STANDING_LEFT])
					{
						willChangeAnimation = true;
						tmp = this->animations[STANDING_LEFT];
					}
				}
			}
			else // it's running
			{
				if (this->facingDirection == RIGHT)
				{
					if (this->currentAnimation != this->animations[RUNNING_RIGHT])
					{
						willChangeAnimation = true;
						tmp = this->animations[RUNNING_RIGHT];
					}
				}
				else // facingDirection == LEFT
				{
					if (this->currentAnimation != this->animations[RUNNING_LEFT])
					{
						willChangeAnimation = true;
						tmp = this->animations[RUNNING_LEFT];
					}
				}
			}
		}
	}

	// *phew*

	if (willChangeAnimation)
	{
		this->currentAnimation->stop();
		this->currentAnimation = tmp;
		this->currentAnimation->start();
	}

	// this was FUCKING UP EVERYTHING
	// it just wouldn't work right
	//
	// i must find a way to get the running animation to change
	// according to the speed
	//
	// while that day never comes, FUCK THIS

	// int newFramerate = (int)fabs((this->vx));
	// this->currentAnimation->setFramerate(newFramerate);
}
void Player::commitMovement()
{
	// Refreshing position
	this->position->x -= (this->box->x - this->desiredPosition->x);
	this->position->y -= (this->box->y - this->desiredPosition->y);

	// Refreshing next bounding box
	this->box->copy(this->desiredPosition);
}
void Player::setHorizontalLimit(int left, int right)
{
	this->leftmostLimitX  = left;
	this->rightmostLimitX = right;

	this->hasHorizontalLimit = true;
}
void Player::setVerticalLimit(int top, int bottom)
{
	this->topLimitY    = top;
	this->bottomLimitY = bottom;

	this->hasVerticalLimit = true;
}
void Player::jump(bool willJump)
{
	if (willJump) // Yay, let's jump!
	{
		if (this->isDoubleJumping) return;

		if (this->isJumping)
			this->isDoubleJumping = true;

		this->inAir     = true;
		this->isJumping = true;

		// Trampoline mode: If you press the jump button twice
		//                  in a row it will jump higher than
		//                  pressing once and then later twice.
		// this->vy += (-1 * this->thrust);

		this->vy = (-0.7 * this->thrust);
	}
	else // Will cancel jumping
	{
		this->inAir     = false;
		this->vy        = 0;
		this->isJumping = false;
		this->isDoubleJumping = false;
	}
}
void Player::fall()
{
	this->inAir = true;
}
void Player::die()
{
	this->isAlive = false;
}
bool Player::died()
{
	if (this->currentAnimation == this->animations[DEATH_RIGHT] ||
	    this->currentAnimation == this->animations[DEATH_LEFT])
		return (this->currentAnimation->isRunning()?
		        false:
		        true);

	return false;
}
bool Player::isHittable()
{
	return (!(this->damaging) && (this->isAlive));
}
bool Player::isFalling()
{
	return (this->vy > 0 ? true : false);
}
void Player::dealDamage()
{
	this->damaging = true;
}
// void Player::stepIntoMovablePlatform(PlatformMovable* platform)
// {
// 	// Watch out for NULL poiters!
// 	this->movablePlatform = platform;
// }
bool Player::Winned()
{
	return this->win;
}

