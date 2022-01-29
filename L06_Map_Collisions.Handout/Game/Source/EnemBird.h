#ifndef __MODULEBIRD_H__
#define  __MODULEBIRD_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class EnemBird : public Module
{
public:
	// Constructor
	EnemBird();

	// Destructor
	~EnemBird();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Awake(pugi::xml_node& config);

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

	//pathfind
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
	//bool ECGrav = true;
	bool Move = false;
	bool MoveY = false;
	bool ECGCollision = false;
	bool EBDead = false;
	bool dead;
	bool PathDet;
	int ECyVel;
	int ECXVel;
	int vides;

	SDL_Texture* TBird;
	SDL_Rect rectBird;


	Animation* currentAnimation;
	Animation idleAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation leftHurtAnim;
	Animation rightHurtAnim;
	Animation rightDeadAnim;
	Animation leftDeadAnim;

	// Countdown to handle shot spacing

	// The player spritesheet loaded into an SDL_Texture
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction


	// The player's collider
	Collider* CBird = nullptr;
	Collider* DetectorBird = nullptr;

	// A flag to detect when the player has been destroyed

};

#endif // __MODULECENTIPIDE_H__

