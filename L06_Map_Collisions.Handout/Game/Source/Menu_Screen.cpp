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
	ConS = app->tex->Load("Assets/textures/Screen/Continue.png");
	OptS = app->tex->Load("Assets/textures/Screen/Options.png");
	ExS = app->tex->Load("Assets/textures/Screen/Exit.png");
	Enter = app->tex->Load("Assets/textures/Screen/enter_image.png");
	MbS = app->tex->Load("Assets/textures/Screen/menu_screen_fons.png");

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	btnPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { 150, 150, 150, 90 }, this);
	btnConf = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test1", { 950, 150, 150, 90 }, this);
	btnOpt  = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Test1", { 150, 500, 150, 90 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Test1", { 950, 500, 150, 90 }, this);
	//btnOpt1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Test1", { 950, 300, 150, 90 }, this);
	//btnOpt2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Test1", { 150, 300, 150, 90 }, this);
	app->Centipide->Disable();

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

	    app->render->DrawTexture(MbS, 0, 0);
		app->render->DrawTexture(playS, 150, 150);
		app->render->DrawTexture(ConS, 950, 150);
		app->render->DrawTexture(OptS, 150, 500);
		app->render->DrawTexture(ExS, 950, 500);

	
	if (EnterScreen == true)
	{
		app->render->DrawTexture(Enter, 0, 0);
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			EnterScreen = false;
		}
	}


	if (EnterScreen == false)
	{
	app->guiManager->Draw();
	}
	return true;
}

// Called each loop iteration
bool Menu_Screen::PostUpdate()
{
	bool ret = true;
	if (EndGame == true) ret = false;
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}


bool Menu_Screen::OnGuiMouseClickEvent(GuiControl* control)
{
	if (Open == true)
	{
		switch (control->type)
		{
		case GuiControlType::BUTTON:
		{
			
				//Checks the GUI element ID
				if (control->id == 1)
				{
					Disable();
					app->scene->Enable();
					app->Centipide->Enable();
					app->scene->EnterScreen = false;
					MenuScreen = false;
					LOG("Click on button 1");
					Open = false;
				}

				else if (control->id == 2)
				{
					Disable();
					app->scene->Enable();
					app->LoadGameRequest();
					app->scene->EnterScreen = false;
					MenuScreen = false;
					LOG("Click on button 2");
					Open = false;
				}

				else if (control->id == 4) {
					EndGame = true;
				}

		default: break;
			}
		}
	
	}
	return true;
}

// Called before quitting
bool Menu_Screen::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
