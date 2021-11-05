#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	float playerX = 60;
	float playerY = 0;
	float playerHeight;
	float TerraY = 875;
	bool isJumping = false;
	float yVel = 0;
	SDL_Texture* player = nullptr;
	Animation idle;
	Animation idleE;
	Animation Dead;
	Animation MoveD;
	Animation MoveE;
	Animation JumpE;
	Animation JumpD;
	Animation* currentAnimation = nullptr;

private:
	SDL_Texture* img;
};

#endif // __SCENE_H__