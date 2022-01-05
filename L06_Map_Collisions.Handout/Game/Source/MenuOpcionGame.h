#ifndef __MENU_SCENE_GAME_H__
#define __MENU_SCENE_GAME_H__

#include "Module.h"
#include "Point.h"
struct SDL_Texture;

class MenuOpcionGame : public Module
{
public:

	MenuOpcionGame();

	// Destructor
	virtual ~MenuOpcionGame();

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

private:

	SDL_Texture* play;
	bool EnterScreen = true;
	SDL_Texture* Enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;
	bool originSelected = false;

};

#endif // __MENU_SCENE_GAME_H__