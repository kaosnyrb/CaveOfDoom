//--------------------------------------------------
// Handle for a Sprite
// One bitmap can have many sprites on it.
// Bryn Stringer F6063476
//--------------------------------------------------
#include <SDL.h>
#include "Bitmap.h"
#include "util_vector2d.h"

#pragma once

class Sprite
{
	private:
	Bitmap* SourceBitmap;
	SDL_Rect TextureArea;
	public:
	int Width;
	int Height;

	Sprite(Bitmap* pSourceBitmap, SDL_Rect pTextureArea)
	{
		SourceBitmap = pSourceBitmap;
		TextureArea = pTextureArea;
		Width = TextureArea.w;
		Height = TextureArea.h;
	}

	SDL_Rect GetTextureArea()
	{
		return TextureArea;
	}
	SDL_Surface* GetSurface()
	{
		return SourceBitmap->GetSurface();
	}
};
