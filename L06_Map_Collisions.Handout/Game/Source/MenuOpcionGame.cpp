#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "MenuOpcionGame.h"
#include "Menu_Screen.h"
#include "EnemCentipide.h"

#include "Defs.h"
#include "Log.h"

MenuOpcionGame::MenuOpcionGame() : Module()
{
	name.Create("Menu");
}

// Destructor
MenuOpcionGame::~MenuOpcionGame()
{

}

// Called before render is available
bool MenuOpcionGame::Awake()
{
	LOG("Loading Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool MenuOpcionGame::Start()
{
	// L03: DONE: Load map
	// L12b: Create walkability map on map loading

	ResS = app->tex->Load("Assets/textures/Screen/resume.png");
	IMenS = app->tex->Load("Assets/textures/Screen/initial_menu.png");
	OptS = app->tex->Load("Assets/textures/Screen/Options.png");
	ExS = app->tex->Load("Assets/textures/Screen/Exit.png");
	return true;
}

// Called each loop iteration
bool MenuOpcionGame::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool MenuOpcionGame::Update(float dt)
{

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	app->render->DrawTexture(ResS, 150, 150);
	app->render->DrawTexture(IMenS, 950, 150);
	app->render->DrawTexture(OptS, 150, 500);
	app->render->DrawTexture(ExS, 950, 500);


	//Resume
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 100 && mouseX < 250 && mouseY > 100 && mouseY < 190) {
		Disable();
		app->scene->Enable();
	}

	//Return menu initial
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 800 && mouseX < 950 && mouseY > 100 && mouseY < 190) {
		Disable();
		app->menu->Enable();
	}
	return true;
}

// Called each loop iteration
bool MenuOpcionGame::PostUpdate()
{
	bool ret = true;
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	//Exit game
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 800 && mouseX < 1050 && mouseY > 500 && mouseY < 590) {
		ret = false;
	}
	return ret;
}

// Called before quitting
bool MenuOpcionGame::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
