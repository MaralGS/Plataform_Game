#include "Player.h"

#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Collisions.h"
#include "Scene.h"
#include "Map.h"


Player::Player() : Module()
{
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
}

Player::~Player()
{

}

bool Player::Start()
{
	bool ret = true;
	Dead.Reset();
	currentAnimation = &idle;
	
	player = app->tex->Load("Assets/textures/SteamMan/Sprites.png");

	/*
	position.x = 40;
	position.y = 24;*/

	// L10: DONE 4: Retrieve the player when playing a second time
	win = false;
	stop = false;

	// L6: DONE 3: Add a collider to the player


	return ret;
}


bool Player::Update(float dt)
{
	app->map->CollisionAdd();
	ColliderP = colliderP.AddCollider(playerX, playerY, 50, 100, Collider::Type::PLAYER);
	colliderP.DebugDraw({ playerX, playerY, 24, 40 }, Collider::Type::PLAYER);
	
	for (int i = 0; app->map->Walls1[i] != nullptr; ++i) {
		WallR->x = app->map->Walls1[i]->rect.x;
		PlayerR->x = ColliderP->rect.x;

		if ((PlayerR->x + 64 >= WallR->x) && (ColliderP->rect.x <= app->map->Walls1[i]->rect.x + 32) &&
			(ColliderP->rect.x + 64 >= app->map->Walls1[i]->rect.y) && (ColliderP->rect.y <= app->map->Walls1[i]->rect.y + 32)) {
			playerY = 0;
		}
	}
		return true;
}


bool Player::PostUpdate()
{
	//God Mode
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && GDMode == true)
	{
		playerY += 2;
		if (currentAnimation != &MoveD)
		{
			MoveD.Reset();
			currentAnimation = &MoveD;
		}


	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && GDMode == true)
	{
		playerY -= 2;
		if (currentAnimation != &MoveD)
		{
			MoveD.Reset();
			currentAnimation = &MoveD;
		}


	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		GDMode = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		GDMode = false;
	}

	//move
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		dx = 1;
		if (currentAnimation != &MoveD)
		{
			MoveD.Reset();
			currentAnimation = &MoveD;
		}

	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		dx = 0;
		if (currentAnimation != &idle)
		{
			idle.Reset();
			currentAnimation = &idle;
		}

	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		dx = -1;
		if (currentAnimation != &MoveE)
		{
			MoveE.Reset();
			currentAnimation = &MoveE;
		}

	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		dx = 0;
		if (currentAnimation != &idleE)
		{
			idleE.Reset();
			currentAnimation = &idleE;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		dy = 1;
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

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		playerX = 0;
		playerY = 0;
		vides = 3;
	}

	dy = -yVel;

	if (dx != 0 || dy != 0)
	{
		playerX += dx;
		playerY += dy;
	}

	if (playerY < app->scene->TerraY && GDMode == false) {
		yVel -= 0.04;
	}


	//dead
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

	
	else {
		yVel = 0;
		isJumping = false;
		playerY = app->scene->TerraY;
		if (app->input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT) {

		}
	}
	
	//draw player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(player, playerX, playerY, &rect);



	return true;
}



