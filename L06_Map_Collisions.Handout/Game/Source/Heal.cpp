#include "Heal.h"

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




Heal::Heal(bool startEnabled) : Module()
{
	idleAnim.PushBack({ 11, 21, 21, 18 });
	idleAnim.PushBack({ 42, 18, 21, 23 });
	idleAnim.PushBack({ 75, 14, 21, 27 });
	idleAnim.PushBack({ 107, 18, 21, 24 });
	idleAnim.PushBack({ 141, 21, 21, 22 });
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;

}

Heal::~Heal()
{
}


bool Heal::Start()
{
	bool ret = true;
	heal = app->tex->Load("Assets/textures/Meat/meat.png");
	currentAnimation = &idleAnim;

	healcol = app->collisions->AddCollider({ Pheal.x,Pheal.y, 21 ,18 }, Collider::Type::HEAL, this);
	return ret;
}

bool Heal::Update(float dt)
{

	return true;
}

bool Heal::PostUpdate()
{

	//draw Centipide
	healrect = currentAnimation->GetCurrentFrame();

	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false && HPup == true)
	{
		app->render->DrawTexture(heal, Pheal.x, Pheal.y, &healrect);
	}
	currentAnimation->Update();

	return true;
}
