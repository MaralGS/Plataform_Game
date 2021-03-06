#include "Collisions.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Scene.h"
#include "SString.h"


Collisions::Collisions() : Module()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ECENTIPIDE] = true;
	matrix[Collider::Type::WALL][Collider::Type::GROUND] = false;
	matrix[Collider::Type::WALL][Collider::Type::ROOF] = false;
	matrix[Collider::Type::WALL][Collider::Type::BIRD] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ECENTIPIDE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ROOF] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BIRD] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DETECTOR1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DETECTOR2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::HEAL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::AUTOSAVE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::COINS] = true;

	matrix[Collider::Type::COINS][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COINS][Collider::Type::GROUND] = false;
	matrix[Collider::Type::COINS][Collider::Type::ECENTIPIDE] = false;
	matrix[Collider::Type::COINS][Collider::Type::BIRD] = false;

	matrix[Collider::Type::ECENTIPIDE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ECENTIPIDE][Collider::Type::ECENTIPIDE] = false;
	matrix[Collider::Type::ECENTIPIDE][Collider::Type::WALL] = true;	
	matrix[Collider::Type::ECENTIPIDE][Collider::Type::GROUND] = true;	
	matrix[Collider::Type::ECENTIPIDE][Collider::Type::ROOF] = true;
	matrix[Collider::Type::ECENTIPIDE][Collider::Type::BIRD] = false;	
	matrix[Collider::Type::ECENTIPIDE][Collider::Type::ATTACK] = true;
	
	matrix[Collider::Type::BIRD][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BIRD][Collider::Type::ECENTIPIDE] = false;
	matrix[Collider::Type::BIRD][Collider::Type::WALL] = true;
	matrix[Collider::Type::BIRD][Collider::Type::GROUND] = true;
	matrix[Collider::Type::BIRD][Collider::Type::ROOF] = true;
	matrix[Collider::Type::BIRD][Collider::Type::BIRD] = false;
	matrix[Collider::Type::BIRD][Collider::Type::ATTACK] = true;
	
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GROUND][Collider::Type::ECENTIPIDE] = true;
	matrix[Collider::Type::GROUND][Collider::Type::WALL] = false;
	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::GROUND][Collider::Type::ROOF] = false;
	matrix[Collider::Type::GROUND][Collider::Type::BIRD] = true;

	matrix[Collider::Type::ROOF][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ROOF][Collider::Type::ECENTIPIDE] = true;
	matrix[Collider::Type::ROOF][Collider::Type::WALL] = false;
	matrix[Collider::Type::ROOF][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ROOF][Collider::Type::ROOF] = false;
	matrix[Collider::Type::ROOF][Collider::Type::BIRD] = true;

	matrix[Collider::Type::ATTACK][Collider::Type::ATTACK] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ATTACK][Collider::Type::ECENTIPIDE] = true;
	matrix[Collider::Type::ATTACK][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::ROOF] = false;
	matrix[Collider::Type::ATTACK][Collider::Type::BIRD] = true;

	matrix[Collider::Type::DETECTOR1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DETECTOR2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HEAL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::AUTOSAVE][Collider::Type::PLAYER] = true;


}

// Destructor
Collisions::~Collisions()
{

}



bool Collisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// Skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// Avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// Skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool Collisions::Update()
{

	return true;
}

bool Collisions::PostUpdate()
{
	if (debug) 
		DebugDraw();

	return true;
}

void Collisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(colliders[i]->rect,  0, 255, 0, alpha);
			break;
		case Collider::Type::GROUND: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha );
			break;
		case Collider::Type::ECENTIPIDE: // Yelow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::ATTACK: // Yelow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::ROOF: // Dark Green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::BIRD: // Dark Green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::DETECTOR1: // skyblue
			app->render->DrawRectangle(colliders[i]->rect, 209, 196, 233, alpha);
			break;
		case Collider::Type::DETECTOR2: // skyblue
			app->render->DrawRectangle(colliders[i]->rect, 209, 196, 233, alpha);
			break;
		case Collider::Type::HEAL: // red
			app->render->DrawRectangle(colliders[i]->rect, 213, 0, 0, alpha);
			break;
		case Collider::Type::AUTOSAVE: // Dark Green
			app->render->DrawRectangle(colliders[i]->rect, 213, 0, 0, alpha);
			break;
		case Collider::Type::COINS: // Dark Green
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		}
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

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

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