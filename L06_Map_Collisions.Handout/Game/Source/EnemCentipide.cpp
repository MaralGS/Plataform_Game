#include "EnemCentipide.h"

#include "App.h"
#include "Textures.h"
#include "Animation.h"
#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Collisions.h"
#include "Scene.h"
#include "Player.h"
#include "PathFinding.h"

#include "Map.h"
#include "Defs.h"
#include "Log.h"




EnemCentipide::EnemCentipide() : Module()
{
	name.Create("Enemy1");
	idleAnim.PushBack({ 7, 7, 47, 35 });

	rightAnim.PushBack({ 224, 93, 47, 35 });
	rightAnim.PushBack({ 152, 94, 46, 34 });
	rightAnim.PushBack({ 80, 93, 47, 35 });
	rightAnim.PushBack({ 8, 92, 48, 36 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Left 
	leftAnim.PushBack({ 7, 50, 47, 35 });
	leftAnim.PushBack({ 80, 51, 46, 34 });
	leftAnim.PushBack({ 151, 50, 47, 35 });
	leftAnim.PushBack({ 222, 49, 48, 36 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	DeathAnim.PushBack({ 10, 382, 47, 35 });
	DeathAnim.PushBack({ 72, 386, 56, 31 });
	DeathAnim.PushBack({ 139, 393, 61, 24 });
	DeathAnim.PushBack({ 213, 394, 59, 23 });
	DeathAnim.loop = false;
	DeathAnim.speed = 0.05f;
}

EnemCentipide::~EnemCentipide()
{
}

bool EnemCentipide::Awake(pugi::xml_node& config) {

	LOG("Loading Enemy 1");
	bool ret = true;
	PEnemy.x = config.child("Position").attribute("PositionX").as_int();
	PEnemy.y = config.child("Position").attribute("PositionY").as_int();
	ECyVel = config.child("Vel").attribute("yVel").as_int();
	ECXVel = config.child("Vel").attribute("xVel").as_int();
	vides = config.child("Vides").attribute("v").as_int();
	dead = config.child("Generals").attribute("dead").as_bool();

	return ret;
}

bool EnemCentipide::Start()
{
	bool ret = true;
	Centipide = app->tex->Load("Assets/Textures/Enemies/Enemy1/centipide.png");
	currentAnimation = &idleAnim;
	//Dead.Reset();
	CentipideC = app->collisions->AddCollider({ PEnemy.x,PEnemy.y, 48 ,36 }, Collider::Type::ECENTIPIDE, this);
	DetectorCentipide = app->collisions->AddCollider({ PEnemy.x - 300,PEnemy.y - 700, 600, 800 }, Collider::Type::DETECTOR1, this);

	return ret;
}

bool EnemCentipide::Update(float dt)
{
	pathfind();
	
	// move
		if (ECGDead == false  && PathDet == false) {
			// esquerra
			if (Move == false)
			{
				currentAnimation = &leftAnim;
				if (PEnemy.x > 550)
				{
					PEnemy.x = PEnemy.x - 3;
				}
				else
				{
					Move = true;
				}
			}
			// dreta
			if (Move == true)
			{
				currentAnimation = &rightAnim;
				if (PEnemy.x < 1200)
				{
					PEnemy.x = PEnemy.x + 3;
				}
				else
				{
					Move = false;
				}
			}
			CentipideC->SetPos(PEnemy.x, PEnemy.y);
		}
		
	//gravity
	{
		if (ECGrav == true && app->scene->EnterScreen == false)
		{
			PEnemy.y += ECyVel;
		}

		if (ECGrav == false && ECGCollision == true)
		{
		//	ECGrav = true;
			ECGCollision = false;
		}

	}
	if (PEnemy.y == 1000) {
		ECGDead = true;
	}
	if (ECGDead == true) {
		LOG("Esta mort? %c", ECGDead);
		currentAnimation = &DeathAnim;
		CentipideC->SetPos(0,0);
	}
	
	if (Debug == true) {
		//Debug Collisions
		app->map->DebugColisions();
		//Debug Player
		app->render->DrawRectangle({ PEnemy.x,PEnemy.y,47,37 }, 255, 140, 0, 80);
	}
	
	return true;
}

bool EnemCentipide::PostUpdate()
{

	//draw Centipide
	rectCentipide = currentAnimation->GetCurrentFrame();

	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false && ECGDead == false)
	{
		app->render->DrawTexture(Centipide, PEnemy.x, PEnemy.y, &rectCentipide);
	}
	currentAnimation->Update();

	return true;
}


void EnemCentipide::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.

	if (c1->type == Collider::Type::ECENTIPIDE && c2->type == Collider::Type::GROUND)
	{
		if (c1->rect.y <= c2->rect.y)
		{
			ECGCollision = true;
			ECGrav = false;
		}
	}

	//path detector
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

void EnemCentipide::pathfind() {
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
			CentipideC->SetPos(PEnemy.x, PEnemy.y);
		}
	}
}