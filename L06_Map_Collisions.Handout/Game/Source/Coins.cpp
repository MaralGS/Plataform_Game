#include "Coins.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Collisions.h"
#include "Scene.h"


Coins::Coins() : Module()
{
	idle.PushBack({ 5, 6, 16, 17 });
	idle.PushBack({ 28, 6, 12, 17 });
	idle.PushBack({ 11, 29, 5, 16 });
	idle.PushBack({ 28, 28, 12, 17 });
	idle.loop = true;
	idle.speed = 0.1f;
}

Coins::~Coins()
{

}

bool Coins::Start()
{

	bool ret = true;

	TextureCoin = app->tex->Load("Assets/textures/Coins.png");

	for (int i = 0; i < NUM_COINS; i++)
	{
		currentAnimation[i] = &idle;
	}

		coin[0] = CreateCoin(700, 700, TextureCoin);
		coin[1] = CreateCoin(500, 700, TextureCoin);


	return ret;
}

bool Coins::Update()
{
	for (int i = 0; i < NUM_COINS; i++)
	{
		currentAnimation[i]->Update();

		if (coin[i].Destroyed)
		{
			coin[i].dead = true;
			coin[i].collider->pendingToDelete = true;
		}
	}
	return true;
}


bool Coins::PostUpdate()
{

	for (int i = 0; i < NUM_COINS; i++)
	{
		if (coin[i].dead == false)
		{
			app->render->DrawTexture(coin[i].coinsT, coin[i].x, coin[i].y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}
	return true;
}



void Coins::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < NUM_COINS; ++i)
	{
		if (coin[i].collider == c1 && !coin[i].Destroyed)
		{
			if (c2->type == Collider::Type::PLAYER)
			{
				coin[i].Destroyed = true;
			}
		}
	}
}

CoinsS Coins::CreateCoin(int x, int y, SDL_Texture* t)
{
	CoinsS Coins;

	Coins.collider = app->collisions->AddCollider({ x, y, 16, 16 }, Collider::Type::COINS, this);
	Coins.coinsT = t;
	Coins.x = x;
	Coins.y = y;

	return Coins;
}