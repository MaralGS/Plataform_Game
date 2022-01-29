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
#include "Collisions.h"

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
	OptS = app->tex->Load("Assets/textures/Screen/options.png");
	ExS = app->tex->Load("Assets/textures/Screen/exit.png");
	MbS = app->tex->Load("Assets/textures/Screen/menu_screen_fons.png");
	ClickFx = app->audio->LoadFx("Assets/audio/fx/click.wav");
	OptionMenu2 = app->tex->Load("Assets/textures/Screen/menu_opcions.png");


	btnPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, "Test1", { 150, 150, 150, 90 }, this);
	btnConf = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 8, "Test1", { 950, 150, 150, 90 }, this);
	btnOpt = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 9, "Test1", { 150, 500, 150, 90 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, "Test1", { 950, 500, 150, 90 }, this);
	btnFullScreen = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 17, "Test1", { 728, 323, 35, 35 }, this);
	btnFullScreen->checked = false;
	FPS = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 18, "Test1", { 726, 450, 35, 35 }, this);
	FPS->checked = false;
	CloseOpt = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 19, "Test1", { 830,215, 35, 35 }, this);

	Volume = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 20, "Test1", { 410, 323, 180, 30 }, this);
	Volume->maxValue = app->audio->maxMusicValue;
	Volume->minValue = 0;
	FX = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 21, "Test1", { 410, 448, 180, 30 }, this);
	FX->maxValue = app->audio->maxFxValue;
	FX->minValue = 0;
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

	if (OptionMenu == true && Opt == false) {
		btnPlay->Draw(app->render);
		btnConf->Draw(app->render);
		btnOpt->Draw(app->render);
		btnExit->Draw(app->render);
	}
	if (Opt == true) {
		app->render->DrawTexture(MbS, 0, 0);
		app->render->DrawTexture(OptionMenu2, 360, 200);
		btnFullScreen->Draw(app->render);
		FPS->Draw(app->render);
		CloseOpt->Draw(app->render);
		Volume->Draw(true, app->render, app->input);
		FX->Draw(true, app->render, app->input);
	}
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
					app->scene->EnterScreen = false;
					app->hud->pause = false;
					LOG("Click on button 1");
					OptionMenu = false;

				}

				if (control->id == 8)
				{
					Disable();
					app->menu->Enable();
					app->guiManager->T2 = false;
					app->guiManager->Sec = 1;
					OptionMenu = false;
					LOG("Click on button 2");

				}
				if (control->id == 9)
				{
					Opt = true;
				}
				if (control->id == 10)
				{
					EndGame = true;
				}
				if (control->id == 19)
				{
					Opt = false;
				}
				//Other cases here

			}
			case GuiControlType::CHECKBOX:
			{
				if (control->id == 17)
				{
					btnFullScreen->checked = !btnFullScreen->checked;
					if (btnFullScreen->checked == true) {
						SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
					}
					else SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_MAXIMIZED);
				}
				if (control->id == 18)
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
				if (control->id == 20)
				{
					app->audio->MusicVolumeControl(Volume->GetValue());
				}
				if (control->id == 21)
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
bool MenuOpcionGame::CleanUp()
{
	LOG("Freeing scene");
	return true;
}
