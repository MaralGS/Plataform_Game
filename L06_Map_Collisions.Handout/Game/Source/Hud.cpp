#include <stdio.h>

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
#include "Hud.h"
#include "Fonts.h"


#include "Map.h"
#include "Defs.h"
#include "Log.h"




Hud::Hud() : Module()
{
	idleAnim.PushBack({ 5, 6, 144, 44 });
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;

}

Hud::~Hud()
{
}


bool Hud::Start()
{
	bool ret = true;
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = app->fonts->Load("Assets/textures/fonts.png", lookupTable,2);
	Vida = app->tex->Load("Assets/textures/cuadrat_puntuacio_vida.png");
	points = app->tex->Load("Assets/textures/cuadrat_puntuacio_vida.png");
	currentAnimation = &idleAnim;

	return ret;
}

bool Hud::Update(float dt)
{
	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
	{
		//points
		sprintf_s(scoreText, "pts;%2d", score);
		//app->fonts->DrawTxt(app->render->camera.x + 30, app->render->camera.y + 350, scoreFont, scoreText);
		app->fonts->DrawTxt(app->player->PPlayer.x - 120, app->player->PPlayer.y - 855, scoreFont, scoreText);

		sprintf_s(scoreText, "hp;%2d", app->player->vides);
		//app->fonts->DrawTxt(app->render->camera.x + 30, app->render->camera.y + 350, scoreFont, scoreText);
		app->fonts->DrawTxt(app->player->PPlayer.x + 980, app->player->PPlayer.y - 855, scoreFont, scoreText);

	}
	
	return true;
}

bool Hud::PostUpdate()
{

	rect = currentAnimation->GetCurrentFrame();

	if (app->scene->DeadScreen == false && app->scene->WScrean == false && app->scene->EnterScreen == false)
	{
		app->render->DrawTexture(points, app->player->PPlayer.x - 140, app->player->PPlayer.y - 550, &rect);
		app->render->DrawTexture(Vida, app->player->PPlayer.x + 970, app->player->PPlayer.y - 550, &rect);
	}
	currentAnimation->Update();

	return true;
}
