#include "App.h"

#include "Attack.h"
#include "Input.h"
#include "Audio.h"
#include "Collisions.h"
#include "Player.h"
#include "Render.h"
#include "EnemCentipide.h"

#include "Defs.h"
#include "Log.h"

#include <stdio.h>
#include <iostream>


Attack::Attack() : Module()
{



}

Attack::~Attack()
{

}

bool Attack::Start()
{
	AttackP = app->collisions->AddCollider({0,0,30,30}, Collider::Type::ATTACK, this);
	return true;
}



bool Attack::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		{
			AttackP->SetPos(app->player->PPlayer.x + 20, app->player->PPlayer.y);
		}
	//AttackP->SetPos(0,0);
	return true;
}



bool Attack::PostUpdate()
{
	return true;
}


void Attack::OnCollision(Collider* c1, Collider* c2)
{
	if ((c1 == AttackP) && (app->player->dead == false))
	{
		if (c1->type == Collider::Type::ATTACK && c2->type == Collider::Type::ECENTIPIDE)
		{
			app->Centipide->CentipideC->pendingToDelete = true;
		}
	}

}