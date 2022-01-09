#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Module.h"
#include "Point.h"
#include "GuiButton.h"
struct SDL_Texture;

class Menu_Screen : public Module
{
public:

	Menu_Screen();

	// Destructor
	virtual ~Menu_Screen();

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

	bool OnGuiMouseClickEvent(GuiControl* control);
	// Called before quitting
	bool CleanUp();

	bool Opt = false;
private:

	SDL_Texture* playS;
	SDL_Texture* play2S;

	SDL_Texture* ConS;
	SDL_Texture* Con2S;
	
	SDL_Texture* OptS;
	SDL_Texture* Opt2S;

	SDL_Texture* ExS;
	SDL_Texture* Ex2S;

	bool EnterScreen = true;
	SDL_Texture* Enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;
	bool originSelected = false;
	GuiButton* btn1;
	GuiButton* btn2;

};

#endif // __MENU_SCENE_H__