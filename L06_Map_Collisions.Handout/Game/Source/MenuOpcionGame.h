#ifndef __MENU_SCENE_GAME_H__
#define __MENU_SCENE_GAME_H__

#include "Module.h"
#include "Point.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"

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

	bool OptionMenu = false;
	
	SDL_Texture* ResS;
	SDL_Texture* IMenS;
	SDL_Texture* OptS;
	SDL_Texture* ExS;
	SDL_Texture* MbS;
	SDL_Texture* OptionMenu2;

private:

	GuiButton* btnPlay;
	GuiButton* btnConf;
	GuiButton* btnOpt;
	GuiButton* btnExit;
	GuiCheckBox* btnFullScreen;
	GuiCheckBox* FPS;
	GuiButton* CloseOpt;
	GuiButton* btnOpt2;
	GuiSlider* Volume;
	GuiSlider* FX;

	bool EnterScreen = true;
	bool Opt = false;
	int ClickFx = 1;
	SDL_Texture* Enter = nullptr;

	bool OnGuiMouseClickEvent(GuiControl* control);
	// L12b: Debug pathfing
	iPoint origin;
	bool originSelected = false;
	bool EndGame = false;

};

#endif // __MENU_SCENE_GAME_H__