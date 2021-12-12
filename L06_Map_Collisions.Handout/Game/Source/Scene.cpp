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
#include "EnemBird.h"
#include "Player.h"
#include "PathFinding.h"
#include "Heal.h"
#include "Collisions.h"
#include "AutoSave.h"
#include "Coins.h"
#include "Hud.h"

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
	//position player
	app->player->PPlayer.x;
	app->player->PPlayer.y;
	//position powerup
	app->heal->Pheal.x = 800;
	app->heal->Pheal.y = 650;
	//position flag
	app->autos->PAsave.x = 1500;
	app->autos->PAsave.y = 790;


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
	if (app->player->PPlayer.x <= 3072) {
		if (app->player->PPlayer.x >= 150) {
			app->render->camera.x = (app->player->PPlayer.x * -1) + 150;
		}
	}

	//float startTicks = SDL_GetTicks();


	// L02: DONE 3: Request Load / Save when pressing L/S


	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		EnterScreen = false;
	}
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		debug = !debug;
	}
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		//Enemy Centipide reset
		app->Centipide->PEnemy.x = 918;
		app->Centipide->PEnemy.y = 870;
		app->Centipide->ECGDead = false;
		//Enemy bird reset
		app->Bird->PEnemy.x = 1400;
		app->Bird->PEnemy.y = 700;
		app->Bird->EBDead = false;
		//screens reset
		WScrean = false;
		DeadScreen = false;
		//power up reset
		app->heal->HPup = true;
		app->heal->healcol->SetPos(600, 700);
		//player reset
		app->player->dead = false;
		app->player->vides = 3;
		app->player->PPlayer.x = 150;
		app->player->PPlayer.y = 875;
		//autosave restart
		app->autos->PAsave.x = 1500;
		app->autos->PAsave.y = 790;
		app->autos->saved = false;
		app->autos->autosave = false;
		app->autos->FlagGreen = false;
		app->coins->Enable();
		app->SaveGameRequest();
	}

	if (app->player->vidaDown == true && app->player->vides != 0 )
	{
		if (app->autos->FlagGreen == false)
		{
			app->player->PPlayer.x = 150;
			app->player->PPlayer.y = 875;
			app->player->vidaDown = false;
		}
	
		else
		{
			app->player->PPlayer.x = 1500;
			app->player->PPlayer.y = 855;
			app->player->vidaDown = false;
		}
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
		app->render->DrawTexture(END, app->player->PPlayer.x - 270, app->player->PPlayer.y - 620);
	}

	if (app->player->PPlayer.x == 4000) {
		WScrean = true;
	}
	if (WScrean == true)
	{
		app->render->DrawTexture(WIN, app->player->PPlayer.x - 270, app->player->PPlayer.y - 615);
	}

		// L12b: Debug pathfinding
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d, FPS: %d , Avf.FPS: %d, Last Ms: %d ",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count(), app->FpsN, app->FpsD, app->Lastms);

	if (debug == true) {
		//Debug Collisions
		app->map->DebugColisions();
		//Debug Player
		app->collisions->DebugDraw();
		//Debug Pathfinding
		app->scene->DebugPath();
	}

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
