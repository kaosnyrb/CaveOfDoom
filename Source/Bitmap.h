//--------------------------------------------------
// Handle for a bitmap
// Bryn Stringer F6063476
//--------------------------------------------------
#include <stdio.h>
#include <SDL.h>

#pragma once
class Bitmap
{
	public:
		Bitmap(const char *Filename, Uint32 AlphaKey = 0)
		{
			SDL_Surface *temp;
			temp = SDL_LoadBMP(Filename);
			if (temp == NULL) 
			{
				printf("Unable to load bitmap: %s\n", SDL_GetError());
				return;
			}
			else
			{
				LoadedImage = SDL_DisplayFormat(temp);
				SDL_FreeSurface(temp);
				src.x = 0;
				src.y = 0;
				src.w = LoadedImage->w;
				src.h = LoadedImage->h;
				SDL_SetColorKey (LoadedImage, SDL_SRCCOLORKEY,AlphaKey);
			}
		}
		~Bitmap()
		{
			SDL_FreeSurface(LoadedImage);
		}
		SDL_Surface* GetSurface()
		{
			return LoadedImage;
		}
		SDL_Rect* GetTextureRect()
		{
			return &src;
		}
		SDL_Surface* LoadedImage;
	private:
		SDL_Rect src;
};
