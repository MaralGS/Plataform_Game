#ifndef __MODULECOLLISIONS_H__
#define __MODULECOLLISIONS_H__

#define MAX_COLLIDERS 100

#include "Module.h"
#include "Collider.h"

class Collisions : public Module
{
public:
	// Constructor
	// Fills all collision matrix data
	Collisions();

	// Destructor
	~Collisions();

	// Called at the beginning of the application loop
	// Removes all colliders pending to delete
	// Checks for new collisions and calls its listeners


	// Called at the middle of the application loop
	// Switches the debug mode on/off
	bool Update();

	// Called at the end of the application loop
	// Draw all colliders (if debug mode is enabled)


	// Removes all existing colliders
	bool CleanUp();

	// Adds a new collider to the list
	Collider* AddCollider(int x, int y, int w, int h, Collider::Type type);

	// Removes the collider memory and removes it from the colliders array
	void RemoveCollider(Collider* collider);

	// Draws all existing colliders with some transparency
	void DebugDraw(SDL_Rect Body, int type);

	void OnCollision(Collider* c1, Collider* c2);
	

private:
	// All existing colliders in the scene
	Collider* colliders[MAX_COLLIDERS] = { nullptr };

	// The collision matrix. Defines the interaction for two collider types
	// If set two false, collider 1 will ignore collider 2
	bool matrix[Collider::Type::MAX][Collider::Type::MAX];

	// Simple debugging flag to draw all colliders
	bool debug = false;
	SDL_Rect ColliderW;
};

#endif // __MODULECOLLISIONS_H__