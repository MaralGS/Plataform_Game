#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "MenuOpcionGame.h"
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
	SDL_Rect Resume = { 100, 100, 150, 90 };
	app->render->DrawRectangle(Resume, 255, 0, 0);

	SDL_Rect Imenu = { 800, 100, 150, 90 };  
	app->render->DrawRectangle(Imenu, 255, 255, 0);

	SDL_Rect Exit = { 800, 500, 150, 90 };
	app->render->DrawRectangle(Exit, 0, 255, 0);  

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	//Resume
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 100 && mouseX < 250 && mouseY > 100 && mouseY < 190) {
		Disable();
		app->scene->Enable();
	}

	//Return menu initial
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 800 && mouseX < 1050 && mouseY > 100 && mouseY < 190) {
		Disable();
		app->OpcionMenu->Enable();
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
