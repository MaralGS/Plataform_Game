#ifndef __MODULEHUD_H__
#define  __MODULEHUD_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class Hud : public Module
{
public:
	// Constructor
	Hud();

	// Destructor
	~Hud();

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
	iPoint Ppoints;
	iPoint PVida;
	// The speed in which we move the player (pixels per frame)
	//player General
	bool Debug = false;
	SDL_Texture* points;
	SDL_Texture* Vida;
	SDL_Rect rect;
	 
	int timerS = 59;
	int timerM = 0;
	int comodin = 0;
	//fonts
	int scoreFont = -1;
	char scoreText[150] = { "\0" };
	int score = 0;

	Animation* currentAnimation;
	Animation idleAnim;
	// Countdown to handle shot spacing

	// The player spritesheet loaded into an SDL_Texture
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction


	// The player's collider

	// A flag to detect when the player has been destroyed

};

#endif // __MODULEHUD_H__

