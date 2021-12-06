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

#include "Map.h"


EnemCentipide::EnemCentipide() : Module()
{
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

}

EnemCentipide::~EnemCentipide()
{

}

bool EnemCentipide::Start()
{
	bool ret = true;
	Centipide = app->tex->Load("Assets/textures/Enemies/Centipide.png");
	currentAnimation = &idleAnim;
	//Dead.Reset();

	PEnemy.x = 250;
	PEnemy.y = 475;
	CentipideC = app->collisions->AddCollider({ PEnemy.x,PEnemy.y, 48 ,36 }, Collider::Type::ECENTIPIDE, this);

	return ret;
}

bool EnemCentipide::Update(float dt)
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
	CentipideC->SetPos(PEnemy.x, PEnemy.y);
	return true;
}

bool EnemCentipide::PostUpdate()
{


	//draw player
	rectCentipide = currentAnimation->GetCurrentFrame();

	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
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

}