#include "Collisions.h"

#include "App.h"

#include "Render.h"
#include "Input.h"
#include "Scene.h"
#include "SString.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::DEATH] = false;
	matrix[Collider::Type::WALL][Collider::Type::FINISH] = false;


	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::DEATH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FINISH] = true;
	

	matrix[Collider::Type::DEATH][Collider::Type::WALL] = false;
	matrix[Collider::Type::DEATH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DEATH][Collider::Type::DEATH] = false;
	matrix[Collider::Type::DEATH][Collider::Type::FINISH] = false;


	matrix[Collider::Type::FINISH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FINISH][Collider::Type::FINISH] = false;
	matrix[Collider::Type::FINISH][Collider::Type::WALL] = false;
	matrix[Collider::Type::FINISH][Collider::Type::DEATH] = false;



}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}
void Module::OnCollision(Collider* c1, Collider* c2)
{

}

bool ModuleCollisions::PreUpdate()
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

bool ModuleCollisions::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) debug = !debug;

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug) DebugDraw();

	return true;
}

void ModuleCollisions::DebugDraw()
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
			app->render->DrawRectangle(colliders[i]->rect,0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(colliders[i]->rect,0, 255, 0, alpha);
			break;
		case Collider::Type::DEATH: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::FINISH: // red
			app->render->DrawRectangle(colliders[i]->rect,255, 0, 0, alpha);
			break;

		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
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

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
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

void ModuleCollisions::RemoveCollider(Collider* collider)
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