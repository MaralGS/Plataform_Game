#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Player.h"
#include "Scene.h"
#include "Menu_Screen.h"

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

	if (app->scene->active == true)
	{
		app->scene->Disable();
	}

	return true;
}

// Called each loop iteration
bool Menu_Screen::PreUpdate()
{
app->render->DrawTexture(play, 100, 100);
	return true;
}

// Called each loop iteration
bool Menu_Screen::Update(float dt)
{
	SDL_Rect Play = {100, 100, 70, 50};
	app->render->DrawRectangle(Play, 255, 0, 0);

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);

	app->render->DrawTexture(play, 100, 100);

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && mouseX > 100 && mouseX < 170 && mouseY >100 && mouseY < 150 ) {
		Disable();
		app->scene->Enable();
	}
	return true;
}

// Called each loop iteration
bool Menu_Screen::PostUpdate()
{
	bool ret = true;
	SDL_Rect l = { 200, 100, 70, 50 };
	app->render->DrawRectangle(l, 255, 255, 0);
	
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Menu_Screen::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
