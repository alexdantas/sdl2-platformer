#ifndef GAMESTATEGAME_H_DEFINED
#define GAMESTATEGAME_H_DEFINED

// Gaaah, #include hell!
#include <vector>
#include <cstdlib>
#include "GameState.hpp"
#include "SDL.hpp"
#include "Window.hpp"
#include "Sprite.hpp"
#include "InputManager.hpp"
#include "Music.hpp"
#include "SFX.hpp"
#include "Player.hpp"
#include "Log.hpp"
#include "BlockManager.hpp"

/// This represents the actual game taking place.
///
/// Here is defined all the game logic and rules.
///
/// ## For developers:
///
/// Before you continue, take a deep breath.
///
/// Done? OK.
/// This is the most complex class of this game and it uses
/// pretty much every other class on the project.
///
/// To understand it you must have a lot of patience and that
/// "I'll see what it means later" feeling.
///
/// Don't try to understand everything at once!
/// Try to abstract a litte and follow the code thinking only in
/// terms of what you think it's doing.
///
/// After you've quite guessed what a method does, start looking
/// into the classes that it uses.
///
class GameStateGame: public GameState
{
public:
    GameStateGame(Window* window);
    virtual ~GameStateGame();

    /// Constructs everything necessary for the game.
    void load(int stack=0);

    /// Destroys anything builded during the game
    int unload();

    /// Updates all possible things on the game.
    ///
    /// @return A status code indicating what to do (should we
    ///         change states/quit the game?). The codes are
    ///         defined on GameState.hpp.
    GameState::StateCode update(float dt);

    /// Shows everything onscreen;
    void render();

private:

    // Internal state-specific methods.
    //
    // They're here to ease reading -  each one of them gets
    // called once per frame.

    /// Receives input and tells what to do with it.
    ///
    /// @note Every class that needs input deals with it internally.
    ///       For example, the Player's input-handling method is
    ///       inside the Player class!
    ///       The input here is specific to the Game State.
    void updateInput();

    /// Checks and resolves all possible collisions
    /// during this state.
    ///
    /// ## For developers
    ///
    /// Instead of each object checking it's collision with
    /// everyone,
    /// I've decided to make each state check AND resolve collisions
    /// for every object it contains.
    ///
    /// It makes more sense since each state needs it's
    /// own collision rules and knows which objects to check
    /// collision for.
    /// (For example, at the main menu I might have platforms there
    ///  but wouldn't want to check collisions for them)
    ///
    /// This way, every object knows how to update and move itself
    /// but the state ALLOWS it or not.
    ///
    /// If the state doesn't allow the object to move, then it will
    /// be stuck, just like when you can't pass through the ground
    /// because the "Physics Rules of the World" don't allow you to
    /// (even though the gravity keeps pulling you every second).
    ///
    void checkCollisions();

    // Now, the variables.

	Window* window;

    bool will_quit;

    Music* bgmusic;

	SFX* sfx;

	Sprite* bg;

    Rectangle* gameArea;

	Player* player;

	BlockManager* blocks;

};

#endif //GAMESTATEGAME_H_DEFINED

