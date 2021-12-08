#ifndef __MODULECENTIPIDE_H__
#define  __MODULECENTIPIDE_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class EnemCentipide : public Module
{
public:
	// Constructor
	EnemCentipide();

	// Destructor
	~EnemCentipide();

	bool Awake(pugi::xml_node& config);
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

	//int Timer(int second);

	//Pathfinding
	void pathfind();

	// Draws gamepad debug info in the screen
	//void DebugDrawGamepadInfo();

public:
	// Position of the player in the map
	iPoint PEnemy;
	// The speed in which we move the player (pixels per frame)
	//player General
	float speed = 0.8f;
	bool Debug = false;
	bool vides;
	bool Move = false;
	bool PathDet = false;
	bool dead;

	bool ECGrav = true;
	bool ECGCollision = false;
	int ECyVel = 5;
	int ECXVel = 5;

	SDL_Texture* Centipide;
	SDL_Rect rectCentipide;


	Animation* currentAnimation;
	Animation idleAnim;
	Animation rightAnim;
	Animation leftAnim;

	// Countdown to handle shot spacing

	// The player spritesheet loaded into an SDL_Texture
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction


	// The player's collider
	Collider* CentipideC = nullptr;
	Collider* DetectorCentipide = nullptr;

	// A flag to detect when the player has been destroyed

};

#endif // __MODULECENTIPIDE_H__

