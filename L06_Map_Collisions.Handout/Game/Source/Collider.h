#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"
#include "Module.h"
#include "Point.h"
#include "App.h"

#define MAX_LISTENERS 5

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		PLAYER,
		WALL,
		DEATH,
		FINISH,
		MAX

	};
public:
	
	// Methods
	Collider(SDL_Rect rectangle, Type type);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;
	iPoint getPos();

	// Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
};


#endif // !__COLLIDER_H__



