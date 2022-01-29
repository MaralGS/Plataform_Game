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
	playS = app->tex->Load("Assets/textures/Screen/play.png");
	ConS = app->tex->Load("Assets/textures/Screen/continue.png");
	OptS = app->tex->Load("Assets/textures/Screen/options.png");
	ExS = app->tex->Load("Assets/textures/Screen/exit.png");
	Enter = app->tex->Load("Assets/textures/Screen/enter_image.png");
	MbS = app->tex->Load("Assets/textures/Screen/menu_screen_fons.png");
	MbS = app->tex->Load("Assets/textures/Screen/menu_screen_fons.png");
	Cred = app->tex->Load("Assets/textures/Screen/credits.png");
	Credclick = app->tex->Load("Assets/textures/Screen/creditsclick.png");
	ClickFx = app->audio->LoadFx("Assets/audio/fx/click.wav");

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	btnPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { 150, 150, 150, 90 }, this);
	btnConf = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test1", { 950, 150, 150, 90 }, this);
	btnOpt  = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Test1", { 150, 500, 150, 90 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Test1", { 950, 500, 150, 90 }, this);
	creditExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Test1", { 478, 598, 383, 100 }, this);
	credit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Test1", { 550, 600, 150, 90 }, this);
	btnFullScreen = new GuiCheckBox(6, { 300, 300, 50, 50 }, "FullScreen");
	btnFullScreen->SetObserver(this);
	//btnOpt2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Test1", { 150, 300, 150, 90 }, this);

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
	
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
	{
		app->audio->PlayFx(ClickFx);
	}
	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	if (Credits == true)
	{
		LOG("Polla");
		app->render->DrawTexture(Cred, 0, 0);
		creditExit->Draw(app->render);
	}


	
	if (EnterScreen == true)
	{
		app->render->DrawTexture(Enter, 0, 0);
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			EnterScreen = false;
		}
	}


	if (EnterScreen == false && Credits == false)
	{
		LOG("Polla");
		app->render->DrawTexture(MbS, 0, 0);
		app->render->DrawTexture(playS, 150, 150);
		app->render->DrawTexture(ConS, 950, 150);
		app->render->DrawTexture(OptS, 150, 500);
		app->render->DrawTexture(ExS, 950, 500);
		app->render->DrawTexture(Credclick, 550, 600);
		btnConf->Draw(app->render);
		btnPlay->Draw(app->render);
		btnOpt->Draw(app->render);
		btnExit->Draw(app->render);
		credit->Draw(app->render);
		btnFullScreen->Draw(app->render);
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
	if (app->guiManager->CheackA1 == true)
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
						app->Centipide->PEnemy.x = 918;
						app->Centipide->PEnemy.y = 870;
						app->Centipide->ECGDead = false;
						app->scene->EnterScreen = false;
						MenuScreen = false;
						app->player->dead = false;
						app->player->vides = 3;
						app->player->PPlayer.x = 150;
						app->player->PPlayer.y = 875;
						app->guiManager->T1 = false;
						app->guiManager->Sec = 1;
						LOG("Click on button 1");

					}

					else if (control->id == 2)
					{
						Disable();
						app->scene->Enable();
						app->LoadGameRequest();
						app->scene->EnterScreen = false;
						MenuScreen = false;
						app->guiManager->T1 = false;
						app->guiManager->Sec = 1;
						LOG("Click on button 2");

					}
					else if (control->id == 3)
					{

						LOG("Click on button 2");
					}
					else if (control->id == 4) {
						EndGame = true;
					}

					else if (control->id == 5)
					{
						Credits = false;

					}
					else if (control->id == 6)
					{
						Credits = true;
						btnConf->state = GuiControlState::NORMAL;
						btnPlay->state = GuiControlState::NORMAL;
						btnOpt->state = GuiControlState::NORMAL;
						btnExit->state = GuiControlState::NORMAL;
						credit->state = GuiControlState::NORMAL;
						LOG("Click on button 2");
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
