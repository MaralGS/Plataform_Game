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
	rightAnim.speed = 0.1f;

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
	TBird = app->tex->Load("Assets/textures/Enemies/Enemi2/Enemy2.png");
	currentAnimation = &idleAnim;
	//Dead.Reset();

	Bird = app->collisions->AddCollider({ PEnemy.x,PEnemy.y, 47,25 }, Collider::Type::BLOATED, this);

	return ret;
}

bool EnemBird::Update(float dt)
{
	//pathfind();
	//gravity
	{
		if (ECGrav == true)
		{
			PEnemy.y += ECyVel;
		}

		if (ECGrav == false && ECGCollision == true)
		{
			ECGrav = true;
			ECGCollision = false;
		}

	}

	if (Debug == true) {
		//Debug Collisions
		app->map->DebugColisions();
		//Debug Player
		app->render->DrawRectangle({ PEnemy.x,PEnemy.y,47,37 }, 255, 140, 0, 80);
	}
	Bird->SetPos(PEnemy.x, PEnemy.y);
	return true;
}

bool EnemBird::PostUpdate()
{


	//draw player
	rectBird = currentAnimation->GetCurrentFrame();

	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
	{
		app->render->DrawTexture(TBird, PEnemy.x, PEnemy.y, &rectBird);
	}
	currentAnimation->Update();

	return true;
}


void EnemBird::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.

	if (c1->type == Collider::Type::BLOATED && c2->type == Collider::Type::GROUND)
	{
		if (c1->rect.y <= c2->rect.y)
		{
			ECGCollision = true;
			ECGrav = false;
		}
	}

}

void EnemBird::pathfind() {

	app->pathfinding->CreatePath(app->map->WorldToMap(PEnemy.x, PEnemy.y), app->map->WorldToMap(app->player->PPlayer.x, app->player->PPlayer.y));
}