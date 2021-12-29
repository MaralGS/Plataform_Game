#include "App.h"

#include "Attack.h"
#include "Input.h"
#include "Audio.h"
#include "Collisions.h"
#include "Player.h"
#include "Render.h"
#include "EnemCentipide.h"
#include "EnemBird.h"

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
			app->Centipide->ECGDead = true;
		}
		if (c1->type == Collider::Type::ATTACK && c2->type == Collider::Type::BIRD)
		{
			app->Bird->EBDead = true;
		}
	}

}