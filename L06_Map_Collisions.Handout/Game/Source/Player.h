#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Collisions.h"
#include "Collider.h"

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
	bool Update();

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	bool PostUpdate();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collisions c1, Collisions c2);

public:
	// Position of the player in the map
	fPoint position;
	fPoint prevposition;

	// The speed in which we move the player (pixels per frame)
	float speed = 0.8f;
	int lifes = 3;
	int timer = 0;
	bool dead = false;
	int vides = 3;
	float yVel = 0;
	bool isJumping = false;
	bool destroyed = false;
	


	int playerX = 60;
	int playerY = 0;


	// Countdown to handle shot spacing

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* player = nullptr;
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction

	// A set of animations
	Animation idle;
	Animation idleE;
	Animation Dead;
	Animation MoveD;
	Animation MoveE;
	Animation JumpE;
	Animation JumpD;
	Animation* currentAnimation = nullptr;


	// The player's collider
	Collisions colliderP;

	// A flag to detect when the player has been destroyed
	bool win = false;
	bool death = false;
	bool stop = false;
};

#endif // __MODULEPLAYER_H__