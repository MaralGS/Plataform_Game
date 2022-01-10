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

	
	// Called before quitting
	bool CleanUp();
	bool EnterScreen = true;

	bool Opt = false;
private:

	SDL_Texture* playS;

	SDL_Texture* ConS;

	SDL_Texture* OptS;

	SDL_Texture* ExS;

	bool OnGuiMouseClickEvent(GuiControl* control);

	SDL_Texture* Enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;
	bool originSelected = false;
	GuiButton* btnPlay;
	GuiButton* btnConf;
	GuiButton* btnOpt;
	GuiButton* btnExit;
	GuiButton* btnOpt1;
	GuiButton* btnOpt2;

};

#endif // __MENU_SCENE_H__