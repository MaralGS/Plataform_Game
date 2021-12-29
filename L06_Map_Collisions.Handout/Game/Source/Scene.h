
#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Point.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene(bool startEnabled);

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

	void DebugPath();

	bool debug = false;

	
	bool EnterScreen = true;
	bool DeadScreen = false;
	bool WScrean = false;
	void calculatedFPS();
	

	SDL_Texture* Enter = nullptr;
	SDL_Texture* END = nullptr;
	SDL_Texture* WIN = nullptr;
	
	float playerHeight;
	
	float fps;
	float Maxfps = 60.0f;
	float frameTime;
private:
	

	SDL_Texture* img;
	SDL_Texture* pathTex;
	SDL_Texture* originTex;

	// L12b: Debug pathfing
	iPoint origin;
	bool originSelected = false;

};

#endif // __SCENE_H__