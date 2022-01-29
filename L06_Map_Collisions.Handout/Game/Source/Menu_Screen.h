#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Module.h"
#include "Point.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
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
	bool EScreen = true;
	bool MenuScreen = true;
	bool Opt = false;
private:

	SDL_Texture* playS;

	SDL_Texture* ConS;

	SDL_Texture* OptS;

	SDL_Texture* ExS;

	SDL_Texture* MbS;

	SDL_Texture* Cred;

	SDL_Texture* Credclick; 

	SDL_Texture* OptionMenu;

	int ClickFx = 1;

	

	SDL_Texture* Enter = nullptr;

	// L12b: Debug pathfing
	iPoint origin;
	bool originSelected = false;
	bool EndGame = false;
	bool Credits = false;
	GuiButton* btnPlay;
	GuiButton* btnConf;
	GuiButton* btnOpt;
	GuiButton* btnExit;
	GuiButton* creditExit;
	GuiButton* credit;
	GuiCheckBox* btnFullScreen;
	GuiButton* btnOpt2;

};

#endif // __MENU_SCENE_H__