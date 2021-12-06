#include "App.h"

#include "Attack.h"
#include "Input.h"
#include "Audio.h"
#include "Collisions.h"
#include "Player.h"


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

	return true;
}



bool Attack::Update()
{

	return true;
}



bool Attack::PostUpdate()
{
	return true;
}


void Attack::OnCollision(Collider* c1, Collider* c2)
{


}