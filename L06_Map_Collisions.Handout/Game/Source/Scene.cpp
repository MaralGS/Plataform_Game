#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Animation.h"
#include <iostream>
using namespace std;

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
	idle.speed = 0.02f;


	idleE.PushBack({ 150, 42, 20, 36 });
	idleE.PushBack({ 102, 42, 21, 36 });
	idleE.PushBack({ 54, 42, 21, 36 });
	idleE.PushBack({ 6, 42, 20, 36 });
	idleE.loop = true;
	idleE.speed = 0.02f;



	//mode Dreta sprites
	MoveD.PushBack({ 2, 80, 24, 34 });
	MoveD.PushBack({ 55, 81, 16, 33 });
	MoveD.PushBack({ 96, 81, 31, 33 });
	MoveD.PushBack({ 146, 80, 31, 33 });
	MoveD.PushBack({ 199, 81, 16, 33 });
	MoveD.PushBack({ 240, 81, 28, 33 });
	MoveD.loop = true;
	MoveD.speed = 0.02f;

	//mode Esquerra sprites
	MoveE.PushBack({ 246, 116, 24, 34 });
	MoveE.PushBack({ 201, 117, 16, 33 });
	MoveE.PushBack({ 145, 117, 31, 33 });
	MoveE.PushBack({ 57, 117, 16, 33 });
	MoveE.PushBack({ 4, 117, 28, 33 });
	MoveE.loop = true;
	MoveE.speed = 0.02f;

	JumpD.PushBack({ 2, 246, 26, 32 });
	JumpD.PushBack({ 55, 245, 16, 33 });
	JumpD.PushBack({ 99, 243, 19, 35 });
	JumpD.PushBack({ 147, 237, 19, 37 });
	JumpD.PushBack({ 194, 241, 19, 34 });
	JumpD.PushBack({ 246, 246, 17, 32 });
	JumpD.loop = false;
	JumpD.speed = 0.06f;

	JumpE.PushBack({ 237, 294, 26, 32 });
	JumpE.PushBack({ 194, 293, 16, 33 });
	JumpE.PushBack({ 147, 291, 19, 35 });
	JumpE.PushBack({ 99, 285, 19, 37 });
	JumpE.PushBack({ 52, 289, 19, 34 });
	JumpE.PushBack({ 2, 294, 17, 32 });
	JumpE.loop = false;
	JumpE.speed = 0.02f;

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
	player = app->tex->Load("Assets/textures/SteamMan/Sprites.png");
	currentAnimation = &idle;

	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	for (int i = 0; app->map->coords[i] != nullptr; ++i) {
		SDL_Rect rectCollider = { app->map->coords[i]->x,app->map->coords[i]->y,48,48 };
		app->render->DrawRectangle(rectCollider, 255, 70, 250);
	}
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	
	


	app->render->camera.y = (playerY * -1) + 550;
	app->render->camera.x = (playerX * -1) + 30;
	
	/*app->render->camera.y = (playerY * -1) + 550 ;
	app->render->camera.x = (playerX * -1) + 30;*/

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	float startTicks = SDL_GetTicks();


    // L02: DONE 3: Request Load / Save when pressing L/S

	if(app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		app->SaveGameRequest();

	//move
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && moveXD == true)
	{
		moveXE = true;
		playerX += xVel;
		if (currentAnimation != &MoveD)
		{
			MoveD.Reset();
			currentAnimation = &MoveD;
		}

	}
	//reset animation
	{
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		if (currentAnimation != &idle)
		{
			idle.Reset();
			currentAnimation = &idle;
		}
	}
	
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		if (currentAnimation != &idleE)
		{
			idleE.Reset();
			currentAnimation = &idleE;
		}
	}
	
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && moveXE == true)
	{
		moveXD = true;
		playerX -= xVel;
		if (currentAnimation != &MoveE)
		{
			MoveE.Reset();
			currentAnimation = &MoveE;
		}

	}

	

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (currentAnimation != &JumpD)
		{
			JumpD.Reset();
			currentAnimation = &JumpD;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{

		if (currentAnimation != &JumpD)
		{
			JumpD.Reset();
			currentAnimation = &JumpD;

		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{

		if (currentAnimation != &JumpE)
		{
			JumpE.Reset();
			currentAnimation = &JumpE;
		}
	}

	//jump
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !isJumping)
	{
		yVel = 3.5;
		isJumping = true;
	}
	//jump
	{
		/*else {
			yVel = 0;
			isJumping = false;
			playerY = TerraY;
			if (app->input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT) {

			}
		}*/
	}

	//dead
	{
		/*if (dead == true)
		{
			playerX = 60;
			playerY = 0;
			vides--;
			dead = false;
		}

		if (playerX == 300)
		{
			dead = true;
		}*/
	}
	//colisions

	app->map->Colisions(playerX);
	for (int i = 0; app->map->coords[i] != nullptr; ++i) {
		//El player està colisionant amb una o més tiles
		if ((playerY < app->map->coords[i]->y) && moveY == true) {
			playerY += yVel;
			if ((playerY + 40 >= app->map->coords[i]->y))
			{
				moveY = false;
			}
		}
		
			if ((playerX == app->map->coords[i]->x +24)) 
			{
			moveXE = false;
			}
			
			/*if ((playerX + 24 == app->map->coords[i]->x)) 
			{
			moveXD = false;
			}*/
	}

	currentAnimation->Update();
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	
	

	//RENDER
	// Draw map
	app->map->Draw();
	app->render->DrawTexture(player, playerX, playerY, &rect);


	SDL_Rect rectPlayer = { playerX,playerY,24,40 };
	app->render->DrawRectangle(rectPlayer, 255, 255, 0);

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more



	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	//calculate frames
	calculatedFPS();
	cout << fps << endl;

	float frameTicks = SDL_GetTicks() - startTicks;
	//limit frames
	if (1000.0f / Maxfps > frameTicks) 
	{
		SDL_Delay(1000.0f / Maxfps - frameTime);
	}

	SDL_GL_SetSwapInterval(1);
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


void Scene::calculatedFPS() {
	/*
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

	currentFrames++;*/
}