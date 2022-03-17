#pragma once 

#include "Engine_Core.h"
#include "util_vector2d.h"
#include "util_bytegrid.h"
#include "Bitmap.h"//For map loading
#include "Enemy.h"


//Number of tiles fitting onscreen + 1 for scrolling;
#define TILE_X_COUNT 12	
#define TILE_Y_COUNT 10 
#define TILECOUNT (TILE_X_COUNT * TILE_Y_COUNT)
#define GAME_ENTITYS 10

class CGame_Core
{
	public:
		CGame_Core(CEngine_Core* pCore);
		~CGame_Core();
		void Main();
		Entity* Entitys[TOTAL_ENTITYS];
		
	private:
		CEngine_Core* EngineCoreAccess;
		int ControlsMain();
		void Move(int direction);
		void MoveThink(Uint32 frames);
		int GetSpriteForColor(SDL_Color Color);
		char GetByteForColor(SDL_Color Color);
		SDL_Color GetMapPixel(Bitmap* Map, int x, int y);
		void SetPlayerAnimation();
		void LoadByteMap();
//		Entity* Tile_Grid[TILE_X_COUNT][TILE_Y_COUNT];
		util_vector2d* PlayerPosition;
		util_bytegrid* Grid;
		util_LargeByteGrid* ByteMap;
		//controls
		bool UP_PRESSED;
		bool DOWN_PRESSED;
		bool LEFT_PRESSED;
		bool RIGHT_PRESSED;
		bool LSHOULDER_PRESSED;
		bool RSHOULDER_PRESSED;
		bool START_PRESSED;
		//Movement
		bool MOVING;
		int DIRECTION;
		Uint32 MoveStart;
		int MoveAnimationTimer;
		int CurrentAnimation;
		void KillPlayer();
		void RefreshPosition();
		//Enemies
		Enemy* Enemies[5];
		//Debug
		Uint32 fpsTicks;
		Uint32 lastTick;
		Uint32 fps;
		Uint32 CountTicks;

};

