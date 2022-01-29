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
#include "Hud.h"



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
	OptionMenu = app->tex->Load("Assets/textures/Screen/menu_opcions.png");
	ClickFx = app->audio->LoadFx("Assets/audio/fx/click.wav");


	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	btnPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { 150, 150, 150, 90 }, this);
	btnConf = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test1", { 950, 150, 150, 90 }, this);
	btnOpt  = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Test1", { 150, 500, 150, 90 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Test1", { 950, 500, 150, 90 }, this);
	creditExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Test1", { 478, 598, 383, 100 }, this);
	credit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Test1", { 550, 600, 150, 90 }, this);
	btnFullScreen = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 12, "Test1", { 728, 323, 35, 35 }, this);
	btnFullScreen->checked = false;
	FPS = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 13, "Test1", { 726, 450, 35, 35 }, this);
	FPS->checked = false;
	CloseOpt = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "Test1", { 830,215, 35, 35 }, this);

	Volume = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 15, "Test1", { 410, 323, 180, 30 }, this);
	Volume->maxValue = app->audio->maxMusicValue;
	Volume->minValue = 0;
	FX = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 16, "Test1", { 410, 448, 180, 30 }, this);
	FX->maxValue = app->audio->maxFxValue;
	FX->minValue = 0;
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
		LOG("hola");
		btnExit->state = GuiControlState::DISABLED;
		btnConf->state = GuiControlState::DISABLED;
		btnPlay->state = GuiControlState::DISABLED;
		btnOpt->state = GuiControlState::DISABLED;
		credit->state = GuiControlState::DISABLED;
		app->render->DrawTexture(Cred, 0, 0);
		creditExit->Draw(app->render);
	}


	
	if (EScreen == true)
	{
		app->render->DrawTexture(Enter, 0, 0);
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			EScreen = false;
		}
	}

	if (EScreen == false && Credits == false && Opt == false)
	{
		LOG("hola");
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
		btnExit->state = GuiControlState::NORMAL;
		btnConf->state = GuiControlState::NORMAL;
		btnPlay->state = GuiControlState::NORMAL;
		btnOpt->state = GuiControlState::NORMAL;
		credit->state = GuiControlState::NORMAL;

		btnFullScreen->state = GuiControlState::DISABLED;
		FPS->state = GuiControlState::DISABLED;
		CloseOpt->state = GuiControlState::DISABLED;
		FX->state = GuiControlState::DISABLED;
		Volume->state = GuiControlState::DISABLED;
	}
	if (Opt == true) {
		app->render->DrawTexture(MbS, 0, 0);
		app->render->DrawTexture(OptionMenu, 360, 200);
		btnFullScreen->Draw(app->render);
		FPS->Draw(app->render);
		CloseOpt->Draw(app->render);
		Volume->Draw(true, app->render, app->input);
		FX->Draw(true, app->render, app->input);
		btnFullScreen->state = GuiControlState::NORMAL;
		FPS->state = GuiControlState::NORMAL;
		CloseOpt->state = GuiControlState::NORMAL;
		FX->state = GuiControlState::NORMAL;
		Volume->state = GuiControlState::NORMAL;
		btnExit->state = GuiControlState::DISABLED;
		btnConf->state = GuiControlState::DISABLED;
		btnPlay->state = GuiControlState::DISABLED;
		btnOpt->state = GuiControlState::DISABLED;
		credit->state = GuiControlState::DISABLED;

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
					app->render->camera.y = (app->player->PPlayer.y * -1) + 550;
					app->render->camera.x = (app->player->PPlayer.x * -1) + 150;
					app->scene->EnterScreen = false;
					MenuScreen = false;
					app->player->dead = false;
					app->player->vides = 3;
					app->player->PPlayer.x = 150;
					app->player->PPlayer.y = 875;
					app->guiManager->T1 = false;
					app->guiManager->Sec = 1;
					app->hud->pause = false;
					LOG("Click on button 1");
					EScreen = true;
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
					app->hud->pause = false;
					EScreen = true;
					LOG("Click on button 2");

				}
				else if (control->id == 3)
				{
					Opt = true;
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
					LOG("Click on button 2");
				}
				else if (control->id == 14)
				{
					Opt = false;
				}
				break;
			}
			case GuiControlType::CHECKBOX:
			{
				if (control->id == 12)
				{
					btnFullScreen->checked = !btnFullScreen->checked;
					if (btnFullScreen->checked == true) {
						SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
					}
					else SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_MAXIMIZED);
				}
				if (control->id == 13)
				{
					FPS->checked = !FPS->checked;
					if (FPS->checked == true) {
						app->Maxfps = false;
					}
					else app->Maxfps = true;
				}
				break;
			}
			case GuiControlType::SLIDER:
			{
				if (control->id == 15)
				{
					app->audio->MusicVolumeControl(Volume->GetValue());
				}
				if (control->id == 16)
				{
					app->audio->FxVolumeControl(FX->GetValue());
				}
				break;
			}
			default: break;
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
