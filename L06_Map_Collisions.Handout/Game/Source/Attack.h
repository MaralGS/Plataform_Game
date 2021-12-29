#ifndef __ATTACK_H__
#define __ATTACK_H__

#include "Module.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class Attack : public Module
{
public:
	// Constructor
	Attack();

	// Destructor
	~Attack();

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
	//bool atackEnable = false;
	Collider* AttackP = nullptr;
};

#endif // __ATTACK_H__
