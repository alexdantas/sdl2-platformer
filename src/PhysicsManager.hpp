#ifndef PHYSICSMANAGER_H_DEFINED
#define PHYSICSMANAGER_H_DEFINED

/// Manages physics of the game and how they relate to the game
/// objects.
///
/// For now a simple wrapper around constants.
class PhysicsManager
{
public:
    static float gravityAcceleration;
    static float airFriction;
    static float groundFriction;

private:
};

#endif //PHYSICSMANAGER_H_DEFINED

