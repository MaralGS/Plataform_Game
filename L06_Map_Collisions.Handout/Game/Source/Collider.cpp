#include "Collider.h"
#include "Scene.h"
#include "Log.h"

Collider::Collider(SDL_Rect rectangle, Type type, Collisions* listener) : rect(rectangle), type(type)
{
	listeners[0] = listener;
}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

iPoint Collider::getPos()
{
	return { rect.x, rect.y };
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	// L6: DONE 1: Check if there is an overlap between argument "r" and property "rect".

	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}

void Collider::AddListener(Collisions* listener)
{
	for (int i = 0; i < MAX_LISTENERS; ++i)
	{
		if (listeners[i] == nullptr)
		{
			listeners[i] = listener;
			break;
		}

		// Simple security check to avoid adding the same listener twice
		else if (listeners[i] == listener) break;
	}
}