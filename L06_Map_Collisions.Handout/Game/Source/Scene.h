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

	bool dead = false;
	bool moveY = true;
	bool moveXD = true;
	bool moveXE = true;
	int vides = 3;
	float playerX = 60;
	float playerY = 600;
	void calculatedFPS();
	bool isJumping = false;
	float yVel = 1;
	float xVel = 1;
	SDL_Texture* player = nullptr;
	Animation idle;
	Animation idleE;
	Animation Dead;
	Animation MoveD;
	Animation MoveE;
	Animation JumpE;
	Animation JumpD;
	Animation* currentAnimation = nullptr;
	float playerHeight;
	float TerraY = 1100;
	float fps;
	float Maxfps = 60.0f;
	float frameTime;



private:
	SDL_Texture* img;
};

#endif // __SCENE_H__