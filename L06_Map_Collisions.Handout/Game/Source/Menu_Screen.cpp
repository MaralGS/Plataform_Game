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
	playS = app->tex->Load("Assets/textures/Screen/Play.png");
	play2S = app->tex->Load("Assets/textures/Screen/Play2.png");
	ConS = app->tex->Load("Assets/textures/Screen/Continue.png");
	Con2S = app->tex->Load("Assets/textures/Screen/Continue2.png");
	OptS = app->tex->Load("Assets/textures/Screen/Options.png");
	Opt2S = app->tex->Load("Assets/textures/Screen/Options2.png");
	ExS = app->tex->Load("Assets/textures/Screen/Exit.png");
	Ex2S = app->tex->Load("Assets/textures/Screen/Exit2.png");
	Enter = app->tex->Load("Assets/textures/Screen/enter_image.png");

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { 0, 0, 160, 40 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);

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
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	app->render->DrawTexture(playS, 150, 150);
	app->render->DrawTexture(ConS, 950, 150);
	app->render->DrawTexture(OptS, 100, 500);
	app->render->DrawTexture(ExS, 800, 500);
	
	if (EnterScreen == true)
	{
		app->render->DrawTexture(Enter, 0, 0);
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			EnterScreen = false;
		}
	}

	// Check
	{
		if (mouseX > 150 && mouseX < 300 && mouseY > 150 && mouseY < 240 && EnterScreen == false) {
			app->render->DrawTexture(play2S, 150, 150);
		}
		
		if (mouseX > 950 && mouseX < 1200 && mouseY > 150 && mouseY < 240 && EnterScreen == false) {
			app->render->DrawTexture(Con2S, 950, 150);
		}

		if (mouseX > 100 && mouseX < 250 && mouseY > 500 && mouseY < 590 && EnterScreen == false)
		{
			app->render->DrawTexture(Opt2S, 100, 500);
		}

		if (mouseX > 800 && mouseX < 1050 && mouseY > 500 && mouseY < 590 && EnterScreen == false) {
			app->render->DrawTexture(Ex2S, 800, 500);
		}
	}

	//click
	{
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

		//Options
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 100 && mouseX < 250 && mouseY > 500 && mouseY < 590 && EnterScreen == false)
		{
			Opt = true;
		}
	}
	if (Opt == true)
	{
	app->guiManager->Draw();
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
