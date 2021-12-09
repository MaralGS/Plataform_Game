#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Animation.h"
#include "EnemCentipide.h"
#include "Player.h"
#include "PathFinding.h"

#include <iostream>
using namespace std;

#include "Defs.h"
#include "Log.h"




Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}



// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	app->map->Load("Mapa2.tmx");
	Enter = app->tex->Load("Assets/textures/Enter_Image.png");
	END = app->tex->Load("Assets/textures/End_Image_2.png");
	WIN = app->tex->Load("Assets/textures/Win_Image.png");
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	app->player->PPlayer.x;
	app->player->PPlayer.y;

	if (app->map->Load("Mapa2.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	pathTex = app->tex->Load("Assets/maps/path.png");
	originTex = app->tex->Load("Assets/maps/x.png");


	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	app->map->DColisions();
	if (app->player->PPlayer.y <= 875){
		if (app->player->PPlayer.y >= 600) {
			app->render->camera.y = (app->player->PPlayer.y * -1) + 550;
		}
	}

	if (app->player->PPlayer.x >= 150) {
		app->render->camera.x = (app->player->PPlayer.x * -1) + 150;
	}

	//float startTicks = SDL_GetTicks();


	// L02: DONE 3: Request Load / Save when pressing L/S


	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		EnterScreen = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		app->player->PPlayer.x = 150;
		app->player->PPlayer.y = 875;
		app->Centipide->PEnemy.x = 918;
		app->Centipide->PEnemy.y = 870;

		app->player->vides = 1;
		WScrean = false;
		DeadScreen = false;
		app->player->dead = false;
	}

	//RENDER
	// Draw map
	if (EnterScreen == false)
	{
		app->map->Draw();
	}


	if (EnterScreen == true)
	{
		app->render->DrawTexture(Enter, 0, 300);
	}

	if (app->player->vides <= 0)
	{
		DeadScreen = true;
	}

	if (DeadScreen == true)
	{
		app->render->DrawTexture(END, -125, 200);
	}

	if (app->player->PPlayer.x == 4000) {
		WScrean = true;
	}
	if (WScrean == true)
	{
		app->render->DrawTexture(WIN, app->player->PPlayer.x - 100, app->player->PPlayer.y - 550);
	}

	//calculate frames
	//calculatedFPS();

	/*float frameTicks = SDL_GetTicks() - startTicks;
	//limit frames
	if (1000.0f / Maxfps > frameTicks)
	{
		SDL_Delay(1000.0f / Maxfps - frameTicks);
	}*/

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more
		// L12b: Debug pathfinding
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count());

	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::DebugPath()
{
	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(pathTex, pos.x, pos.y);
	}
}


/*void Scene::calculatedFPS() {
	
	
	static const int NUM_SAMPLES = 10;
	static float frametimes[NUM_SAMPLES];
	static int currentFrames = 0;

	static float prevTicks = SDL_GetTicks();

	float currenTicks;
	currenTicks = SDL_GetTicks();

	frameTime = currenTicks - prevTicks;
	frametimes[currentFrames % NUM_SAMPLES] = frameTime;

	prevTicks = currenTicks;

	int count;

	currentFrames++;
	if (currentFrames < NUM_SAMPLES)
	{
		count = currentFrames;
	}

	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frametimes[i];
	}

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		fps = 60.0f;
	}

	
}*/