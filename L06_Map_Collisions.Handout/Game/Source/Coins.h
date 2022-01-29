#ifndef __COINS_H__
#define __COINS_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"

#define NUM_COINS 100

struct SDL_Texture;

struct CoinsS {
	Collider* collider = nullptr;
	SDL_Texture* coinsT = nullptr;

	int x;
	int y;
	bool Destroyed = false;
	uint dCount = 0;
	bool dead = false;
};

class Coins : public Module
{
public:
	//Constructor
	Coins();

	//Destructor
	~Coins();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start();

	bool Update(float dt);

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate();

	void OnCollision(Collider* c1, Collider* c2) override;

public:

	iPoint position;


	SDL_Texture* TextureCoin = nullptr;

	int coinFx = 0;

	CoinsS coin[NUM_COINS] = { nullptr };

	CoinsS CreateCoin(int x, int y, SDL_Texture* t);

	Animation* currentAnimation[NUM_COINS] = { nullptr };
	Animation idle;
	Animation dead;

};

#endif