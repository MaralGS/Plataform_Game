#include "ModuleEnemy.h"

#include "App.h"

#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Collisions.h"
#include "Player.h"
#include "Enemy.h"
#include "GEnemy.h"


#include "Defs.h"
#include "Log.h"



#define SPAWN_MARGIN 50


ModuleEnemy::ModuleEnemy()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemy::~ModuleEnemy()
{

}

bool ModuleEnemy::Start()
{
	//enemyTexture = app->textures->Load("Assets/enemies/enemies.png");
	//enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			SpawnEnemy(spawnQueue[i]);
			spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
		}
	}

	return true;
}

bool ModuleEnemy::Update(float dt)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->Update();

			if (enemies[i]->death)
			{
				if (enemies[i]->cooldown >= 100)
				{
					delete enemies[i];
					enemies[i] = nullptr;
				}
				else
				{
					enemies[i]->cooldown++;
				}
			}
		}
	}

	return true;
}

bool ModuleEnemy::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return true;
}

// Called before quitting
bool ModuleEnemy::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemy::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemy::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			/*switch (info.type)
			{
			case Enemy_Type::BROWNROBOT:
				enemies[i] = new Enemy_BrownRobot(info.x, info.y);
				break;
			}
			enemies[i]->texture = enemyTexture;
			break;
		}*/
		}
	}
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			

		}

	}

}


