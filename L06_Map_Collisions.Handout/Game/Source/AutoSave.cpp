#include "AutoSave.h"

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




AutoSave::AutoSave() : Module()
{
	RedFlag.PushBack({ 119, 5, 76, 128 });

	GreenFlag.PushBack({ 13, 5, 76, 128 });
}

AutoSave::~AutoSave()
{
}


bool AutoSave::Start()
{
	bool ret = true;
	Asave = app->tex->Load("Assets/textures/Flags.png");
	currentAnimation = &RedFlag;

	Asavecol = app->collisions->AddCollider({ PAsave.x - 5,PAsave.y - 650, 80 ,800 }, Collider::Type::AUTOSAVE, this);
	return ret;
}

bool AutoSave::Update(float dt)
{
	if (autosave == false)
	{
			currentAnimation = &RedFlag;
	}

	if (autosave == true && FlagGreen == false)
	{
			currentAnimation = &GreenFlag;
			FlagGreen = true;
			saved = true;
			
	}
		
	if (saved == true)
	{
		app->SaveGameRequest();
		saved = false;
	}
	Asavecol->SetPos(PAsave.x, PAsave.y);
	return true;
}

bool AutoSave::PostUpdate()
{

	//draw Centipide
	Asaverect = currentAnimation->GetCurrentFrame();

	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false && autosave == false)
	{
		app->render->DrawTexture(Asave, PAsave.x, PAsave.y, &Asaverect);
	}
	
	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false && autosave == true)
	{
		app->render->DrawTexture(Asave, PAsave.x, PAsave.y, &Asaverect);
	}
	currentAnimation->Update();

	return true;
}
