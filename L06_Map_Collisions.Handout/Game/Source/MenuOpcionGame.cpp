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
#include "GuiManager.h"
#include "Hud.h"

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
	MbS = app->tex->Load("Assets/textures/Screen/menu_screen_fons.png");
	ClickFx = app->audio->LoadFx("Assets/audio/fx/click.wav");
	

	btnPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "Test1", { 150, 150, 150, 90 }, this);
	btnConf = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "Test1", { 950, 150, 150, 90 }, this);
	btnOpt = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "Test1", { 150, 500, 150, 90 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "Test1", { 950, 500, 150, 90 }, this);
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

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
	{
		app->audio->PlayFx(ClickFx);
	}

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	app->render->DrawTexture(MbS, 0, 0);
	app->render->DrawTexture(ResS, 150, 150);
	app->render->DrawTexture(IMenS, 950, 150);
	app->render->DrawTexture(OptS, 150, 500);
	app->render->DrawTexture(ExS, 950, 500);

	app->guiManager->Draw();

	return true;
}

// Called each loop iteration
bool MenuOpcionGame::PostUpdate()
{

	bool ret = true;
	if (EndGame == true) ret = false;
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	return ret;
}

bool MenuOpcionGame::OnGuiMouseClickEvent(GuiControl* control)
{
	if (app->guiManager->CheackA1 == false)
	{
		switch (control->type)
		{
			case GuiControlType::BUTTON:
			{
				//Checks the GUI element ID
				if (control->id == 7)
				{
					Disable();
					app->scene->Enable();
					app->guiManager->Sec = 1;
					app->hud->pause = false;
					LOG("Click on button 1");

				}

				if (control->id == 8)
				{
					Disable();
					app->menu->Enable();
					app->guiManager->T2 = false;
					app->guiManager->Sec = 1;
					LOG("Click on button 2");

				}

				if (control->id == 10)
				{
					EndGame = true;
				}
				//Other cases here

			default: break;
			}
		}
	}
	return true;
}

// Called before quitting
bool MenuOpcionGame::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
