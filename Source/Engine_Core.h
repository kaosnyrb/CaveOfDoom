#ifndef _ENGINE_CORE
#define _ENGINE_CORE

#include "SDL.h"
#include <stdio.h>
#include "Bitmap.h"
#include "Sprite.h"
#include "Entity.h"
#include "Sound.h"
#include "util_vector2d.h"
#include "util_bytegrid.h"
#include <vector>
#include <SDL_thread.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define TOTAL_BITMAPS 2
#define TOTAL_SPRITES 22
#define TOTAL_ENTITYS 10

//CONTROL DEFS
#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_Y               (14)
#define GP2X_BUTTON_X               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)

class CEngine_Core
{
	public:
		CEngine_Core();
		~CEngine_Core();
		bool Engine_Running;
		bool Menu;
		void Main();
		SDL_Rect MakeSDL_Rect(int pH,int pW,int pX,int pY);
		void AddEntityToRenderList(Entity* pEntity);
		void SetByteGrid( util_bytegrid* SetGrid )
		{
			Grid = SetGrid;
		}
		void ClearRenderList();
		void PlaySound(int id);
		void SetOffset(int x,int y) { xOffset = x; yOffset = y; }
	private:
		int GetIdForByte(char pchar);
		SDL_Surface *screen; //This pointer will reference the backbuffer 
		SDL_AudioSpec *Audio_Spec; //This point contains the audio access
		// For FPS Calculations
		long fps;
		long fpsTicks;
		long fpsCounter;
		// Last update timer
		long lastTick;
		int xOffset;
		int yOffset;
		//Graphics
		Bitmap* Bitmaps[TOTAL_BITMAPS];
		Sprite* Sprites[TOTAL_SPRITES];
		Entity* Entitys[TOTAL_ENTITYS];
		Sound* Sounds[TOTAL_SOUNDS];
		util_bytegrid* Grid;
};

#endif

