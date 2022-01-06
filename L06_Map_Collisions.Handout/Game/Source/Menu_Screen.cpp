#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "Menu_Screen.h"
#include "EnemCentipide.h"
#include "MenuOpcionGame.h"
#include "GuiManager.h"


#include "Defs.h"
#include "Log.h"

Menu_Screen::Menu_Screen() : Module()
{
	name.Create("Menu");
}

// Destructor
Menu_Screen::~Menu_Screen()
{

}

// Called before render is available
bool Menu_Screen::Awake()
{
	LOG("Loading Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Menu_Screen::Start()
{
	// L03: DONE: Load map
	// L12b: Create walkability map on map loading
	play = app->tex->Load("Assets/textures/Screen/Play.png");
	Enter = app->tex->Load("Assets/textures/Screen/enter_image.png");

	if (app->scene->active == true)
	{
		app->scene->Disable();
	}
	if (app->OpcionMenu->active == true)
	{
		app->OpcionMenu->Disable();
	}
	return true;
}

// Called each loop iteration
bool Menu_Screen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Menu_Screen::Update(float dt)
{
	SDL_Rect Play = {100, 100, 150, 90};
	app->render->DrawRectangle(Play, 255, 0, 0);

	SDL_Rect Continue = { 800, 100, 150, 90 };
	app->render->DrawRectangle(Continue, 255, 255, 0);
	
	SDL_Rect Exit = { 800, 500, 150, 90 };
	app->render->DrawRectangle(Exit, 0, 255, 0);

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	//app->render->DrawTexture(play, 100, 100);
	
	if (EnterScreen == true)
	{
		app->render->DrawTexture(Enter, 0, 0);
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			EnterScreen = false;
		}
	}

	//Play
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 100 && mouseX < 250 && mouseY > 100 && mouseY < 190 && EnterScreen == false ) {
		Disable();
		app->scene->Enable();
		app->Centipide->Enable();
		app->scene->EnterScreen = false;

	}

	//continue
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 800 && mouseX < 1050 && mouseY > 100 && mouseY < 190 && EnterScreen == false ) {
		Disable();
		app->scene->Enable();
		app->LoadGameRequest();
		app->scene->EnterScreen = false;
	}




	return true;
}

// Called each loop iteration
bool Menu_Screen::PostUpdate()
{
	bool ret = true;
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	//Exit
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 800 && mouseX < 1050 && mouseY > 500 && mouseY < 590 && EnterScreen == false ) {
		ret = false;
	}
	return ret;
}


bool Menu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1)
		{
			LOG("Click on button 1");
		}

		if (control->id == 2)
		{
			LOG("Click on button 2");
		}

	}
	//Other cases here

	default: break;
	}

	return true;
}

// Called before quitting
bool Menu_Screen::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
