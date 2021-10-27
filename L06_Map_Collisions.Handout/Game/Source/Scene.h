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

	float playerX = 50;
	float playerY = 50;
	float TerraY = 500;
	SDL_Texture* player = nullptr;
	Animation idle;
	Animation Dead;
	Animation MoveD;
	Animation MoveE;
	Animation Jump;
	Animation* currentAnimation = nullptr;

private:
	SDL_Texture* img;
};

#endif // __SCENE_H__