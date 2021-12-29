#include "Coins.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Collisions.h"
#include "Scene.h"
#include "Hud.h"


Coins::Coins() : Module()
{
	idle.PushBack({ 5, 6, 16, 17 });
	idle.PushBack({ 28, 6, 12, 17 });
	idle.PushBack({ 11, 29, 5, 16 });
	idle.PushBack({ 28, 28, 12, 17 });
	idle.loop = true;
	idle.speed = 0.001f;
}

Coins::~Coins()
{

}

bool Coins::Start()
{

	bool ret = true;

	TextureCoin = app->tex->Load("Assets/Textures/Coins/coins.png");
	
	for (int i = 0; i < NUM_COINS; i++)
	{
		currentAnimation[i] = &idle;
	}

		coin[0] = CreateCoin(348, 768, TextureCoin);
		coin[1] = CreateCoin(392, 768, TextureCoin);
		coin[2] = CreateCoin(440, 768, TextureCoin);
		coin[3] = CreateCoin(488, 768, TextureCoin);

		coin[4] = CreateCoin(970, 864, TextureCoin);
		coin[5] = CreateCoin(1000, 864, TextureCoin);
		coin[6] = CreateCoin(1030, 864, TextureCoin);
		coin[7] = CreateCoin(1060, 864, TextureCoin);
		coin[8] = CreateCoin(1090, 864, TextureCoin);


		coin[9] = CreateCoin(864, 648, TextureCoin);
		coin[10] = CreateCoin(894, 648, TextureCoin);
		coin[11] = CreateCoin(924, 648, TextureCoin);
		coin[12] = CreateCoin(954, 648, TextureCoin);

		coin[13] = CreateCoin(1944, 792, TextureCoin);
		coin[14] = CreateCoin(1992, 792, TextureCoin);
		coin[15] = CreateCoin(2040, 792, TextureCoin);
		coin[16] = CreateCoin(2088, 792, TextureCoin);

		coin[18] = CreateCoin(2568, 696, TextureCoin);
		coin[19] = CreateCoin(2616, 696, TextureCoin);
		coin[20] = CreateCoin(2664, 696, TextureCoin);

		coin[21] = CreateCoin(2904, 360, TextureCoin);
		coin[22] = CreateCoin(2952, 360, TextureCoin);

		coin[23] = CreateCoin(2952, 456, TextureCoin);
		coin[24] = CreateCoin(3000, 456, TextureCoin);

		coin[25] = CreateCoin(3000, 552, TextureCoin);
		coin[26] = CreateCoin(3048, 552, TextureCoin);

		coin[27] = CreateCoin(3048, 648, TextureCoin);
		coin[28] = CreateCoin(3096, 648, TextureCoin);

		coin[31] = CreateCoin(3720, 888, TextureCoin);
		coin[32] = CreateCoin(3768, 888, TextureCoin);
		coin[32] = CreateCoin(3816, 888, TextureCoin);

		coin[33] = CreateCoin(3720, 744, TextureCoin);
		coin[34] = CreateCoin(3768, 744, TextureCoin);
		coin[35] = CreateCoin(3816, 744, TextureCoin);

		coin[36] = CreateCoin(3816, 600, TextureCoin);
		coin[37] = CreateCoin(3864, 600, TextureCoin);

		coin[38] = CreateCoin(3528, 504, TextureCoin);
		coin[39] = CreateCoin(3576, 504, TextureCoin);
		coin[40] = CreateCoin(3624, 504, TextureCoin);

		coin[41] = CreateCoin(3720, 432, TextureCoin);
		coin[42] = CreateCoin(3768, 432, TextureCoin);
		coin[43] = CreateCoin(3816, 432, TextureCoin);


	return ret;
}

bool Coins::Update(float dt)
{
	for (int i = 0; i < NUM_COINS; i++)
	{
		currentAnimation[i]->Update();

		if (coin[i].Destroyed == true)
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
		if (coin[i].dead == false && app->scene->EnterScreen == false && app->scene->DeadScreen == false && app->scene->WScrean == false)
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
				app->hud->score += 100;
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