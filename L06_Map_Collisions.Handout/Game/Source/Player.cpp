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

	// L10: DONE 4: Retrieve the player when playing a second time

	// L6: DONE 3: Add a collider to the player
	
	PlayerC = app->collisions->AddCollider({ PPlayer.x,PPlayer.y,24,36 }, Collider::Type::PLAYER, this);

	return ret;
}

bool Player::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		GodMode = !GodMode;
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


	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
	{
		//move
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && moveXD == true)
		{
			moveXE = true;
			PPlayer.x += xVel;
			if (currentAnimation != &MoveD)
			{
				MoveD.Reset();
				currentAnimation = &MoveD;
			}

		}


		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && moveXE == true)
		{
			moveXD = true;
			PPlayer.x -= xVel;
			if (currentAnimation != &MoveE)
			{
				MoveE.Reset();
				currentAnimation = &MoveE;
			}

		}
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && GodMode == true) {
			if (currentAnimation != &MoveD)
			{
				PPlayer.y -= xVel;
				MoveD.Reset();
				currentAnimation = &MoveD;
			}

		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && GodMode == true) {
			if (currentAnimation != &MoveD)
			{
				PPlayer.y += yVel;
				MoveD.Reset();
				currentAnimation = &MoveD;
			}

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
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && moveY == false && GodMode == false)
	{
		PPlayer.y -= yVel + 100;
		moveY = true;
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

		if (dead == true && GodMode == false)
		{
			PPlayer.x = 150;
			PPlayer.y = 875;
			vides--;

		}

		if (PPlayer.y == 1200)
		{
			dead = true;
		}
}
	//gravity
	{
		if (Grav == true)
		{
			PPlayer.y += yVel;
		}

		if (GCollsion == false)
		{
			Grav = true;
		}
	}
	//SDL_Rect PlayerCollider = { PPlayer.x, PPlayer.y, 48, 48 };
	//app->render->DrawRectangle(PlayerCollider, 255, 255, 0, 80);
	app->map->DrawColisions();
	PlayerC->SetPos(PPlayer.x, PPlayer.y);
	return true;
	
}

bool Player::PostUpdate()
{

	
	//draw player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	
	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
	{
		app->render->DrawTexture(player,PPlayer.x, PPlayer.y, &rect);
	}



	return true;
}


void Player::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if ((c1 == PlayerC) && (dead == false))
	{
		if (godmode == false)
		{
			/*if (c1 == PlayerC && dead == false) {

				switch (c2->type) {
				case Collider::Type::GROUND:
					if (c1->rect.y < c2->rect.y) // up
					{

					}
					if (Grav == true)
					{
						if (c1->rect.y  > c2->rect.y - 36 ) // down
						{
							Grav = false;
						}
					}
					break;

				case Collider::Type::WALL:
					if (c1->rect.x < c2->rect.x + 36) // left
					{
						moveXE = false;
					}
					
					/*if (c1->rect.x + 36 < c2->rect.x) // right
					{
						moveXD = false;
					};
					break;
				} */ 

				//Ground
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::GROUND)
				{
					
					if (c1->rect.y + 36 >= c2->rect.y)
					{
						Grav = false;
						GCollsion = true;
					}
				}
				//Wall left
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
				{
				if (c1->rect.x+ 3 >= c2->rect.x + c2->rect.w )
					{
						moveXE = false;
					}
				}
				//Wall right
				if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
				{
					if (c1->rect.x + c1->rect.w - 2 <= c2->rect.x )
					{
						moveXD = false;
					}
				}
				
			
		}
	}
}
