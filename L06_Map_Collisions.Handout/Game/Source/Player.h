#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class Player : public Module
{
public:
	// Constructor
	Player();

	// Destructor
	~Player();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start();

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update(float dt);

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	bool PostUpdate();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2);


	// Draws gamepad debug info in the screen
	//void DebugDrawGamepadInfo();

public:
	// Position of the player in the map
	iPoint PPlayer;
	// The speed in which we move the player (pixels per frame)
	float speed = 0.8f;
	int timer = 0;

	int vides = 1;
	bool isJumping = false;
	bool GodMode = false;
	bool Debug = false;
	bool dead = false;
	bool moveY = true;
	bool moveXD = true;
	bool moveXE = true;
	bool Grav = true;
	bool GCollision = false;

	int yVel = 1;
	int xVel = 5;
	



	// Countdown to handle shot spacing

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* player;
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	SDL_Rect rectplayer;
	Animation* currentAnimation;

	// A set of animations
	Animation idle;
	Animation idleE;
	Animation Dead;
	Animation MoveD;
	Animation MoveE;
	Animation JumpE;
	Animation JumpD;


	// The player's collider
	Collider* PlayerC = nullptr;

	// A flag to detect when the player has been destroyed
	bool godmode = false;
	bool win = false;
	bool death = false;
	bool stop = false;
};

#endif // __MODULEPLAYER_H__