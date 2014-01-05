#ifndef GAMEOBJECT_H_DEFINED
#define GAMEOBJECT_H_DEFINED

#include "Shapes.hpp"

/// Abstract stuff for any kind of game object.
///
/// Nothing special here, move along.
///
/// The collision scheme was based on Rodrigo Monteiro's awesome
/// "Guide to Implementing 2D Platformers":
/// http://higherorderfun.com/blog/2012/05/20/the-guide-to-implementing-2d-platformers/
///
class GameObject
{
public:
    GameObject(float x=0.0, float y=0.0, int w=0, int h=0);

    ~GameObject();

    /// Updates all the object's internal states.
    virtual void update(float dt) = 0;

    /// Shows object onscreen.
    virtual void render(float cameraX, float cameraY) = 0;

    /// Tells if we've collided with another thing.
    bool collidedWith(GameObject* other);

    /// Places this object on top of the *other*.
    ///
    /// Very specific for collision on platforms.
    ///
    /// @note Doesn't deal with the X axis, Y axis only!
    ///
    void placeOnTop(GameObject* other);

    float getX();
    float getY();
    float getCenterX();
    float getCenterY();
    int   getWidth();
    int   getHeight();

    /// Object's x/y position.
    Point* position;

    /// Object's bounding box size and position.
    ///
    /// ## For developers
    ///
    /// I've splitted the position and bouding box because
    /// not always we have the whole sprite as the bounding box.
    ///
    /// Sometimes the sprite has transparent parts and we need
    /// to adapt the bonding box inside it.
    ///
    /// But in the simplest case, it doesn't make a difference, so
    /// even if the sprite is the whole bouding box this will not
    /// interfere.
    ///
    Rectangle* box;
};

#endif /* GAMEOBJECT_H_DEFINED */
