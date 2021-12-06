#include "EnemBloated.h"

#include "App.h"
#include "Textures.h"
#include "Animation.h"
#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Collisions.h"
#include "Scene.h"

#include "Map.h"


EnemBloated::EnemBloated() : Module()
{
	idleAnim.PushBack({ 16, 11, 46, 48 });

	rightAnim.PushBack({ 376, 147, 46, 48 });
	rightAnim.PushBack({ 303, 146, 46, 49 });
	rightAnim.PushBack({ 232, 146, 45, 50 });
	rightAnim.PushBack({ 161, 147, 44, 48 });
	rightAnim.PushBack({ 89, 146, 44, 49 });
	rightAnim.PushBack({ 16, 145, 45, 50 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Left 
	leftAnim.PushBack({ 16, 77, 46, 48 });
	leftAnim.PushBack({ 88, 76, 46, 49 });
	leftAnim.PushBack({ 160, 75, 45, 50 });
	leftAnim.PushBack({ 232, 77, 44, 48 });
	leftAnim.PushBack({ 304, 76, 44, 49 });
	leftAnim.PushBack({ 376, 75, 45, 50 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

}

EnemBloated::~EnemBloated()
{

}

bool EnemBloated::Start()
{
	bool ret = true;
	Bloated = app->tex->Load("Assets/textures/Enemies/Enemi2/Enemi2.png");
	currentAnimation = &idleAnim;
	//Dead.Reset();

	PEnemy.x = 800;
	PEnemy.y = 600;
	BloatedC = app->collisions->AddCollider({ PEnemy.x,PEnemy.y, 46 ,48 }, Collider::Type::BLOATED, this);

	return ret;
}

bool EnemBloated::Update(float dt)
{
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
	BloatedC->SetPos(PEnemy.x, PEnemy.y);
	return true;
}

bool EnemBloated::PostUpdate()
{


	//draw player
	rectBloated = currentAnimation->GetCurrentFrame();

	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
	{
		app->render->DrawTexture(Bloated, PEnemy.x, PEnemy.y, &rectBloated);
	}
	currentAnimation->Update();

	return true;
}


void EnemBloated::OnCollision(Collider* c1, Collider* c2)
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
