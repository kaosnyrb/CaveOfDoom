#include "util_vector2d.h"
#include "Game_Core.h"

class Enemy
{
	public :
	int SpriteID;
	util_vector2d* OnscreenPosition;
	util_vector2d* WorldPosition;
	bool Active;
	bool OnScreen;
	int PartrolDirection;
	long LastTick;
	Uint32 MoveStart;
	util_LargeByteGrid* Map;
	bool IsMoving;
	Enemy()
	{
		SpriteID = 4;
		WorldPosition = new util_vector2d(0,0);
		OnscreenPosition = new util_vector2d(-100,-100);
		PartrolDirection = 1;
		IsMoving = false;
		MoveStart = 0;
	}
	Enemy(int Sprite, util_vector2d* Position, util_LargeByteGrid* MapPointer)
	{
		SpriteID = Sprite;
		WorldPosition = Position;
		OnscreenPosition = new util_vector2d(-100,-100);
		PartrolDirection = 1;
		Map = MapPointer;
		LastTick = SDL_GetTicks();
		MoveStart = 0;
	}
	bool Think(util_vector2d* PlayerPosition, bool Moving, int MoveDirection)
	{
		int XOffset = 0;
		int YOffset = 0;
		//Set the objects onscreen position, if it is onscreen
		int TimePassed = SDL_GetTicks() - MoveStart;
		int distance = (32 * TimePassed) / 200;
		if ( distance > 32 ) {distance = 32;}
		//printf("Dis = %i\n", distance);
		if ( Moving )
		{
			switch(MoveDirection)
			{
				case 0:
					YOffset =  -32;
					break;
				case 1:
					XOffset =  -32;
					break;
				case 2:
					YOffset =  32;
					break;
				case 3:
					XOffset =  32;
					break;
			}
		}

		switch(PartrolDirection)
		{
				case 0:
					YOffset += -distance + 32;
					break;
				case 1:
					XOffset += distance - 32;
					break;
				case 2:
					YOffset += distance - 32; 
					break;
				case 3:
					XOffset += -distance +32; 
					break;
		}


	
		//Add moving logic here
		if ( LastTick + 200 < SDL_GetTicks())
		{
			if ( PartrolDirection == 1)
			{
				if ( Map->Byte_Grid[WorldPosition->x + 1 - 7][WorldPosition->y - 6] == '0' )
				{
					WorldPosition->x++;
					LastTick = SDL_GetTicks();
					MoveStart = SDL_GetTicks();
				}
				else
				{
					PartrolDirection = 3;
				}
			}
			if ( PartrolDirection == 3 )
			{
				if ( Map->Byte_Grid[WorldPosition->x - 8][WorldPosition->y - 6] == '0' )
				{
					WorldPosition->x--;
					LastTick = SDL_GetTicks();
					MoveStart = SDL_GetTicks();
				}
				else
				{
					PartrolDirection = 1;
				}
			}
			if ( PartrolDirection == 0 )
			{
				if ( Map->Byte_Grid[WorldPosition->x - 7][WorldPosition->y - 1 - 6] == '0' )
				{
					WorldPosition->y--;
					LastTick = SDL_GetTicks();
					MoveStart = SDL_GetTicks();
				}
				else
				{
					PartrolDirection = 2;
				}
			}
			if ( PartrolDirection == 2 )
			{
				if ( Map->Byte_Grid[WorldPosition->x - 7][WorldPosition->y + 1 - 6] == '0' )
				{
					WorldPosition->y++;
					LastTick = SDL_GetTicks();
					MoveStart = SDL_GetTicks();
				}
				else
				{
					PartrolDirection = 0;
				}
			}
		}
		OnScreen = false;
		int deltaX = WorldPosition->x - PlayerPosition->x;
		int deltaY = WorldPosition->y - PlayerPosition->y;
		if ( deltaX <= 7 && deltaX >= -7 )
		{
			if ( deltaY < 6 && deltaY > -6 )
			{
				OnScreen = true;
				//Move it to the correct place onscreen
				int XOnscreen = (deltaX + 4) * 32;
				int YOnscreen = (deltaY + 3) * 32;
				OnscreenPosition->x = XOnscreen + XOffset;
				OnscreenPosition->y = YOnscreen + YOffset;
			}
		}
		return OnScreen;
	}
};
