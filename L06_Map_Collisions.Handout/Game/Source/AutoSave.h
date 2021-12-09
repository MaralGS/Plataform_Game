#ifndef __AUTOSAVE_H__
#define  __AUTOSAVE_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class AutoSave : public Module
{
public:
	// Constructor
	AutoSave();

	// Destructor
	~AutoSave();

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

	// Draws gamepad debug info in the screen
	//void DebugDrawGamepadInfo();

public:
	// Position of the player in the map
	iPoint PAsave;
	// The speed in which we move the player (pixels per frame)
	//player General
	float speed = 0.8f;
	bool Debug = false;
	bool HPup = true;
	SDL_Texture* Asave;
	SDL_Rect Asaverect;


	Animation* currentAnimation;
	Animation idleAnim;
	// Countdown to handle shot spacing

	// The player spritesheet loaded into an SDL_Texture
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction


	// The player's collider
	Collider* Asavecol = nullptr;

	// A flag to detect when the player has been destroyed

};

#endif // __AUTOSAVE_H__

