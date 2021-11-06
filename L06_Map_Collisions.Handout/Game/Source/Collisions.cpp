#include "Collisions.h"

#include "App.h"

#include "Render.h"
#include "Input.h"
#include "Scene.h"
#include "SString.h"
#include "Module.h"

Collisions::Collisions() : Module()
{


}

// Destructor
Collisions::~Collisions()
{

}


bool Collisions::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) debug = !debug;

	return true;
}


void Collisions::DebugDraw(SDL_Rect Body, int type)
{
	Uint8 alpha = 80;


		switch (type)
		{
		case Collider::Type::NONE: // white
			app->render->DrawRectangle(Body, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			app->render->DrawRectangle(Body,0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(Body,0, 255, 0, alpha);
			break;
		case Collider::Type::DEATH: // red
			app->render->DrawRectangle(Body, 255, 0, 0, alpha);
			break;
		case Collider::Type::FINISH: // red
			app->render->DrawRectangle(Body,255, 0, 0, alpha);
			break;

		}
}

// Called before quitting
bool Collisions::CleanUp()
{


	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* Collisions::AddCollider(int x, int y, int w, int h, Collider::Type type)
{
	Collider* ret = nullptr;
	SDL_Rect wall;
	ColliderW.x = x;
	ColliderW.y = y;
	ColliderW.w = w;
	ColliderW.h = h;
	wall = SDL_Rect({ x, y, w, h });
	ret = new Collider(wall,type);
	return ret;
}

void Collisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}
void Collisions::OnCollision(Collider* c1, Collider* c2) {

}