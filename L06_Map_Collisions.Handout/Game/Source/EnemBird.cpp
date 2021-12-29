#include "EnemBird.h"

#include "App.h"
#include "Textures.h"
#include "Animation.h"
#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Collisions.h"
#include "Scene.h"
#include "PathFinding.h"
#include "Player.h"

#include "Map.h"
#include "Defs.h"
#include "Log.h"


EnemBird::EnemBird() : Module()
{
	name.Create("Enemy2");
	idleAnim.PushBack({ 17, 19, 37, 25 });

	rightAnim.PushBack({ 162, 68, 37, 25 });
	rightAnim.PushBack({ 114, 70, 37, 19 });
	rightAnim.PushBack({ 66, 64, 37, 27 });
	rightAnim.PushBack({ 17, 67, 38, 24 });
	rightAnim.loop = true;
	rightAnim.speed = 1.0f;

	// Left 
	leftAnim.PushBack({ 17, 19, 37, 25 });
	leftAnim.PushBack({ 65, 21, 37, 19 });
	leftAnim.PushBack({ 113, 15, 35, 27 });
	leftAnim.PushBack({ 161, 18, 38, 24 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;
	
	leftHurtAnim.PushBack({ 27, 113, 38, 24 });
	leftHurtAnim.PushBack({ 75, 25, 37, 25 });
	leftHurtAnim.loop = true;
	leftHurtAnim.speed = 0.1f;

	rightHurtAnim.PushBack({ 69, 159, 39, 24 });
	rightHurtAnim.PushBack({ 23, 160, 36, 25 });
	rightHurtAnim.loop = true;
	rightHurtAnim.speed = 0.1f;

	leftDeadAnim.PushBack({ 17, 205, 37, 27 });
	leftDeadAnim.PushBack({ 65, 215, 38, 21 });
	leftDeadAnim.PushBack({ 113, 222, 38, 14 });
	leftDeadAnim.PushBack({ 161, 225, 37, 11 });
	leftDeadAnim.loop = true;
	leftDeadAnim.speed = 0.1f;

	rightDeadAnim.PushBack({ 157, 253, 37, 27 });
	rightDeadAnim.PushBack({ 108, 263, 38, 21 });
	rightDeadAnim.PushBack({ 60, 270, 38, 14 });
	rightDeadAnim.PushBack({ 13, 273, 37, 11 });
	rightDeadAnim.loop = true;
	rightDeadAnim.speed = 0.1f;

}

EnemBird::~EnemBird()
{

}

bool EnemBird::Awake(pugi::xml_node& config) {

	LOG("Loading Enemy 2");
	bool ret = true;
	PEnemy.x = config.child("Position").attribute("PositionX").as_int();
	PEnemy.y = config.child("Position").attribute("PositionY").as_int();
	ECyVel = config.child("Vel").attribute("yVel").as_int();
	ECXVel = config.child("Vel").attribute("xVel").as_int();
	vides = config.child("Vides").attribute("v").as_int();
	dead = config.child("Generals").attribute("dead").as_bool();

	return ret;
}


bool EnemBird::Start()
{
	bool ret = true;
	TBird = app->tex->Load("Assets/textures/Enemies/Enemy2/enemy2.png");
	currentAnimation = &idleAnim;
	//Dead.Reset();

	CBird = app->collisions->AddCollider({ PEnemy.x,PEnemy.y, 47,25 }, Collider::Type::BIRD, this);
	DetectorBird = app->collisions->AddCollider({ PEnemy.x - 300,PEnemy.y - 700, 600, 800 }, Collider::Type::DETECTOR1, this);
	return ret;
}

bool EnemBird::Update(float dt)
{
	pathfind();
		// move
	{
		if (EBDead == false && PathDet == false)
		{
			// esquerra
			PEnemy.x;
			if (Move == false)
			{
				currentAnimation = &leftAnim;

				if (PEnemy.y > 500)
				{
					PEnemy.y = PEnemy.y - 3;
				}
				else
				{
					Move = true;
				}
			}
			// dreta
			if (Move == true)
			{
				currentAnimation = &leftAnim;
				if (PEnemy.y < 800)
				{
					PEnemy.y = PEnemy.y + 3;
				}
				else
				{
					Move = false;
				}
			}
			CBird->SetPos(PEnemy.x, PEnemy.y);
		}

		/*if (EBDead == false && PathDet == true) {
			// esquerra
			if (Move == false)
			{	
				currentAnimation = &leftAnim;
				PEnemy.x++;
			}
			// dreta
			else if (Move == true)
			{
				currentAnimation = &rightAnim;
				PEnemy.x--;
			}
			CBird->SetPos(PEnemy.x, PEnemy.y);
			
			// Up
			if (MoveY == false)
			{
				PEnemy.y++;
				currentAnimation = &leftAnim;
			}
			// Down
			else if (MoveY == true)
			{
				currentAnimation = &rightAnim;
				PEnemy.y--;
			}
			CBird->SetPos(PEnemy.x, PEnemy.y);
		}*/
	}

	if (EBDead == true) {
		//currentAnimation = &DeathAnim;
		CBird->SetPos(0, 0);
	}
	if (Debug == true) {
		//Debug Collisions
		app->map->DebugColisions();
		//Debug Player
		app->render->DrawRectangle({ PEnemy.x,PEnemy.y,47,37 }, 255, 140, 0, 80);
	}
	
	return true;
}

bool EnemBird::PostUpdate()
{
	//draw player
	rectBird = currentAnimation->GetCurrentFrame();

	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false && EBDead == false)
	{
		app->render->DrawTexture(TBird, PEnemy.x, PEnemy.y, &rectBird);
	}
	currentAnimation->Update();

	return true;
}


void EnemBird::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.

	if (c1->type == Collider::Type::BIRD && c2->type == Collider::Type::GROUND)
	{
		if (c1->rect.y <= c2->rect.y)
		{
			ECGCollision = true;

		}
	}
	{
		if (c1->type == Collider::Type::DETECTOR1 && c2->type == Collider::Type::PLAYER)
		{
			PathDet = true;
		}
		else
		{
			PathDet = false;
		}
	}

}

void EnemBird::pathfind() {
	if (PathDet == true)
	{
		app->pathfinding->CreatePath(app->map->WorldToMap(PEnemy.x, PEnemy.y), app->map->WorldToMap(app->player->PPlayer.x, app->player->PPlayer.y));

		const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			if (app->player->PPlayer.x < pos.x)
			{
				PEnemy.x--;
			}
			else if (app->player->PPlayer.x > pos.x)
			{
				PEnemy.x++;
			}
			
			if (app->player->PPlayer.y < pos.y)
			{
				PEnemy.y--;
			}
			else if (app->player->PPlayer.y > pos.y)
			{
				PEnemy.y++;
			}
			CBird->SetPos(PEnemy.x, PEnemy.y);
		}
	}
}