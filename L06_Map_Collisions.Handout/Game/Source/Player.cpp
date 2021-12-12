#include "Player.h"

#include "App.h"
#include "Textures.h"
#include "Animation.h"
#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Collisions.h"
#include "Scene.h"
#include "EnemCentipide.h"
#include "Attack.h"
#include "Heal.h"
#include "AutoSave.h"

#include "Map.h"
#include "Defs.h"
#include "Log.h"

Player::Player() : Module()
{
	name.Create("player");

	//idle anim
	idle.PushBack({ 4, 4, 20, 36 });
	idle.PushBack({ 51, 4, 21, 36 });
	idle.PushBack({ 99, 4, 21, 36 });
	idle.PushBack({ 148, 4, 20, 36 });
	idle.loop = true;
	idle.speed = 0.1f;

	//idle Amim Esquerra
	idleE.PushBack({ 150, 42, 20, 36 });
	idleE.PushBack({ 102, 42, 21, 36 });
	idleE.PushBack({ 54, 42, 21, 36 });
	idleE.PushBack({ 6, 42, 20, 36 });
	idleE.loop = true;
	idleE.speed = 0.1f;



	//move Dreta sprites
	MoveD.PushBack({ 2, 80, 24, 34 });
	MoveD.PushBack({ 55, 81, 16, 33 });
	MoveD.PushBack({ 96, 81, 31, 33 });
	MoveD.PushBack({ 146, 80, 31, 33 });
	MoveD.PushBack({ 199, 81, 16, 33 });
	MoveD.PushBack({ 240, 81, 28, 33 });
	MoveD.loop = true;
	MoveD.speed = 0.1f;

	//move Esquerra sprites
	MoveE.PushBack({ 246, 116, 24, 34 });
	MoveE.PushBack({ 201, 117, 16, 33 });
	MoveE.PushBack({ 145, 117, 31, 33 });
	MoveE.PushBack({ 57, 117, 16, 33 });
	MoveE.PushBack({ 4, 117, 28, 33 });
	MoveE.loop = true;
	MoveE.speed = 0.1f;

	// jump right
	JumpD.PushBack({ 2, 246, 26, 32 });
	JumpD.PushBack({ 55, 245, 16, 33 });
	JumpD.PushBack({ 99, 243, 19, 35 });
	JumpD.PushBack({ 147, 237, 19, 37 });
	JumpD.PushBack({ 194, 241, 19, 34 });
	JumpD.PushBack({ 246, 246, 17, 32 });
	JumpD.loop = false;
	JumpD.speed = 0.2f;

	// jump left
	JumpE.PushBack({ 237, 294, 26, 32 });
	JumpE.PushBack({ 194, 293, 16, 33 });
	JumpE.PushBack({ 147, 291, 19, 35 });
	JumpE.PushBack({ 99, 285, 19, 37 });
	JumpE.PushBack({ 52, 289, 19, 34 });
	JumpE.PushBack({ 2, 294, 17, 32 });
	JumpE.loop = false;
	JumpE.speed = 0.2f;

	//atackD
	AtackD.PushBack({ 2, 337, 17, 36 });
	AtackD.PushBack({ 50, 337, 17, 36 });
	AtackD.PushBack({ 97, 335, 19, 38 });
	AtackD.PushBack({ 146, 340, 26, 33 });
	AtackD.PushBack({ 194, 342, 25, 31 });
	AtackD.PushBack({ 242, 339, 17, 34 });
	AtackD.loop = false;
	AtackD.speed = 0.2f;

	//atackE
	AtackE.PushBack({ 242, 390, 17, 36 });
	AtackE.PushBack({ 194, 390, 17, 36 });
	AtackE.PushBack({ 145, 388, 19, 38 });
	AtackE.PushBack({ 89, 393, 26, 33 });
	AtackE.PushBack({ 42, 395, 25, 31 });
	AtackE.PushBack({ 2, 392, 17, 34 });
	AtackE.loop = false;
	AtackE.speed = 0.2f;
}

Player::~Player()
{

}

bool Player::Awake(pugi::xml_node& config) {

	LOG("Loading Player");
	bool ret = true;
	PPlayer.x = config.child("Position").attribute("PositionX").as_int();
	PPlayer.y = config.child("Position").attribute("PositionY").as_int();
	yVel = config.child("Vel").attribute("yVel").as_int();
	xVel = config.child("Vel").attribute("xVel").as_int();
	vides = config.child("Vides").attribute("v").as_int();
	isJumping = config.child("Generals").attribute("isJumping").as_bool();
	GodMode = config.child("Generals").attribute("GodMode").as_bool();
	dead = config.child("Generals").attribute("dead").as_bool();

	return ret;
}

bool Player::Start()
{
	bool ret = true;
	player = app->tex->Load("Assets/textures/SteamMan/Sprites.png");
	currentAnimation = &idle;
	//Dead.Reset();

	// L10: DONE 4: Retrieve the player when playing a second time

	// L6: DONE 3: Add a collider to the player
	
	PlayerC = app->collisions->AddCollider({ PPlayer.x,PPlayer.y,24,36 }, Collider::Type::PLAYER, this);

	return ret;
}

bool Player::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (GodMode == false)
		{
			GodMode = true;
			
		}
		else
		{
			GodMode = false;
			GCollision = true;
		}
		
	}

	//atack
	if (atackX == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		{
			app->attack->AttackP->SetPos(PPlayer.x + 20, PPlayer.y);
			AtackD.Reset();
			currentAnimation = &AtackD;
		}

		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_UP)
		{
			app->attack->AttackP->SetPos(0, 0);
		}
	}
	
	if (atackX == false)
	{
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		{
			app->attack->AttackP->SetPos(PPlayer.x - 20, PPlayer.y);
						AtackE.Reset();
			currentAnimation = &AtackE;
		}

		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_UP)
		{
			app->attack->AttackP->SetPos(0, 0);
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

	//movement
	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
	{
		//move
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && moveXD == true)
		{
			atackX = true;
			JumpESprite = true;
			JumpDSprite = true;
			moveXE = true;
			PPlayer.x += xVel;
			if (jumping2 == false)
			{
				if (currentAnimation != &MoveD)
				{
					MoveD.Reset();
					currentAnimation = &MoveD;
				}
			}
		}


		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && moveXE == true)
		{
			atackX = false;
			moveXD = true;
			JumpDSprite = false;
			JumpESprite = false;
			PPlayer.x -= xVel;
			if (jumping2 == false)
			{
				if (currentAnimation != &MoveE)
				{
					MoveE.Reset();
					currentAnimation = &MoveE;
				}
			}
	

		}
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && GodMode == true) {
			if (currentAnimation != &MoveD)
			{
				PPlayer.y -= xVel;
			}

		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && GodMode == true) {
			if (currentAnimation != &MoveD)
			{
				PPlayer.y += yVel;
			}

		}
		//gravity
		{
			if (GodMode == false)
			{
				if (Grav == true)
				{
					PPlayer.y += yVel;
				}

				if (Grav == false && GCollision == true)
				{
					Grav = true;
					GCollision = false;
				}
			}
		

		}
		//jump
		{
 			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && moveY == false)
			{	
					Sec = 3;
					jumping2 = true;
					if (JumpDSprite == true)
					{
						if (currentAnimation != &JumpD)
						{
							JumpD.Reset();
							currentAnimation = &JumpD;

						}
					}


					if (JumpESprite == false)
					{
						if (currentAnimation != &JumpE)
						{
							JumpE.Reset();
							currentAnimation = &JumpE;
						}
					}
					jumping = true;
					moveY = true;
					GCollision = false;
			}

			if (jumping == true)
			{
				PPlayer.y = PPlayer.y - 10;

					if (timer <= 10) {
						timer++;
					}
					//redueix els sec quan timer esta en 60 i reseteja
					if (timer == 10) {
						timer = 0;
						Sec--;
					}
					else if (Sec == 0) {
						jumping = false;
					}
				//Timer(Sec);
				
			}
			
		}
	}

	
	//dead
	{
		if (PPlayer.y == 1000)
		{
			vides--;
			vidaDown = true;
			if (vides == 0 && GodMode == false && app->autos->FlagGreen == false)
			{
				dead = true;
			}
		}
	}
	
	//SDL_Rect PlayerCollider = { PPlayer.x, PPlayer.y, 48, 48 };
	//app->render->DrawRectangle(PlayerCollider, 255, 255, 0, 80);
	
	PlayerC->SetPos(PPlayer.x, PPlayer.y);
	return true;
}

bool Player::PostUpdate()
{
	//draw player
	rectplayer = currentAnimation->GetCurrentFrame();
	
	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
	{
		app->render->DrawTexture(player,PPlayer.x, PPlayer.y, &rectplayer);
	}
	currentAnimation->Update();

	return true;
}


void Player::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if ((c1 == PlayerC) && (dead == false))
	{
		if (GodMode == false)
		{
				//Ground gravity
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::GROUND)
			{
				if (c1->rect.y + 25 <= c2->rect.y /* || c1->rect.x + 24 <= c2->rect.x*/)
				{
					GCollision = true;
					Grav = false;
					moveY = false;
					jumping2 = false;
				}
			}

			//Wall left
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
			{
				if (c1->rect.x + 3 >= c2->rect.x + c2->rect.w)
				{
					moveXE = false;
				}
			}
			//Wall right
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
			{
				if (c1->rect.x + c1->rect.w - 2 <= c2->rect.x)
				{
					moveXD = false;
				}
			}

			//Roof
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ROOF)
			{
				Sec = 0;
			}
			//Centipide
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ECENTIPIDE)
			{
				vides--;
				vidaDown = true;
				if (vides == 0)
				{
					dead = true;
				}
			}
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BIRD)
			{
				vides--;
				vidaDown = true;
				if (vides == 0)
				{
					dead = true;
				}

			}
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::HEAL)
			{
				vides++;
				app->heal->HPup = false;
				app->heal->healcol->SetPos(0, 0);
			}
			
			if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::AUTOSAVE)
			{
				app->autos->autosave = true;
			}

		}
	}
}

