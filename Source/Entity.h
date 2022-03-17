//--------------------------------------------------
// Handle for a Entity
// One Sprite can be in many places.
// Bryn Stringer F6063476
//--------------------------------------------------
#include <SDL.h>
#include "Sprite.h"
#include "util_vector2d.h"

class Entity
{
	public:
	Sprite* SourceSprite;
	int SpriteID;
	util_vector2d Position;
	bool Active;
	Entity(Sprite* pSourceSprite, util_vector2d pPosition)
	{
		SourceSprite = pSourceSprite;
		Position = pPosition;
		Active = true;
	}
	Entity(int pSpriteID,util_vector2d pPosition)
	{
		SpriteID = pSpriteID;
		Position = pPosition;
		Active = true;
	}
};
