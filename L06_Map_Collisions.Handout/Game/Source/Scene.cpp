#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Animation.h"


#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");

	//idle anim
	idle.PushBack({ 4, 4, 20, 36 });
	idle.PushBack({ 51, 4, 21, 36 });
	idle.PushBack({ 99, 4, 21, 36 });
	idle.PushBack({ 148, 4, 20, 36 });
	idle.loop = true;
	idle.speed = 0.2f;

	/*
	idleE.PushBack({ 4, 4, 20, 36 });
	idleE.PushBack({ 51, 4, 21, 36 });
	idleE.PushBack({ 99, 4, 21, 36 });
	idleE.PushBack({ 148, 4, 20, 36 });
	idleE.loop = true;
	idleE.speed = 0.2f;*/



	//mode Dreta sprites
	MoveD.PushBack({ 2, 80, 24, 34 });
	MoveD.PushBack({ 55, 81, 16, 33 });
	MoveD.PushBack({ 96, 81, 31, 33 });
	MoveD.PushBack({ 146, 80, 31, 33 });
	MoveD.PushBack({ 199, 81, 16, 33 });
	MoveD.PushBack({ 240, 81, 28, 33 });
	MoveD.loop = true;
	MoveD.speed = 0.2f;

	//mode Esquerra sprites
	MoveE.PushBack({ 246, 116, 24, 34 });
	MoveE.PushBack({ 201, 117, 16, 33 });
	MoveE.PushBack({ 145, 117, 31, 33 });
	MoveE.PushBack({ 57, 117, 16, 33 });
	MoveE.PushBack({ 4, 117, 28, 33 });
	MoveE.loop = true;
	MoveE.speed = 0.2f;

	currentAnimation = &idle;

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
	//app->map->Load("hello.tmx");
	app->map->Load("Mapa.tmx");
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	player = app->tex->Load("Assets/textures/SteamMan/Sprites.png");
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

	// Draw map
	app->map->Draw();

	//draw player

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(player, playerX, playerY, &rect);
	currentAnimation = &idle;

	app->render->camera.y = (playerY * -1) + 600;
	app->render->camera.x = (playerX * -1) + 30;

    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		playerX += 0.5f;
		if (currentAnimation != &MoveD)
		{
			currentAnimation = &MoveD;
		}
		MoveD.Reset();
		
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (currentAnimation != &MoveE)
		{
			MoveE.Reset();
			currentAnimation = &MoveE;
		}
		playerX -= 0.5f;
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
	
		playerY -= 2;
	}
	if (playerY != TerraY){
		playerY += 0.5;
	}
	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more



	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

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
