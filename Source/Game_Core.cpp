//----------------------------------------------------
// Game functions
//----------------------------------------------------
#include "Game_Core.h"

CGame_Core::CGame_Core(CEngine_Core* pCore)
{
	EngineCoreAccess = pCore;
	UP_PRESSED = false;
	DOWN_PRESSED = false;
	LEFT_PRESSED = false;
	RIGHT_PRESSED = false;
	LSHOULDER_PRESSED = false;
	RSHOULDER_PRESSED = false;
	START_PRESSED = false;
	MOVING = false;
	for ( int i = 0; i < GAME_ENTITYS;i++ )
	{
		Entitys[i] = new Entity(4,util_vector2d(0,0));
		Entitys[i]->Active = false;
		printf("Entity %i Created\n", i);
	}
	//Load the map
	Grid = new util_bytegrid();
	ByteMap = new util_LargeByteGrid();
	LoadByteMap();
	EngineCoreAccess->SetByteGrid(Grid);
	//General entitys.
	Entitys[0] = new Entity(1,util_vector2d(136,100));
	//EngineCoreAccess->PlaySound(1);//music
	lastTick = SDL_GetTicks();
	PlayerPosition = new util_vector2d(64,64);
	CurrentAnimation = 0;//Movement;
	//DEBUG
	CountTicks = 0;
	Move(2);//Setup the screen
	//TEST
	Entitys[1] = new Entity(4,util_vector2d(-100,-100));
	Entitys[1]->Active = false;
	for ( int i = 0; i < 5; i++ )
	{
		Enemies[i] = new Enemy(4,new util_vector2d(0,0),ByteMap); 
	}
	Enemies[1]->WorldPosition = new util_vector2d(37,87);
	Enemies[1]->PartrolDirection = 1;
	Enemies[2]->WorldPosition = new util_vector2d(25,81);
	Enemies[2]->PartrolDirection = 1;
	Enemies[3]->WorldPosition = new util_vector2d(23,63);
	Enemies[3]->PartrolDirection = 0;
	Enemies[4]->WorldPosition = new util_vector2d(60,73);
	Enemies[4]->PartrolDirection = 1;
}

CGame_Core::~CGame_Core()
{

}

void CGame_Core::Main()
{
	ControlsMain();
	//Debug/timing
	fpsTicks = SDL_GetTicks() - lastTick;
	CountTicks = CountTicks + fpsTicks;
	if ( fpsTicks > 0 )
	{
		fps = 1000 / fpsTicks; 
	}
	lastTick = SDL_GetTicks();
	if ( CountTicks > 1000 )
	{
		printf("FPS = %i \n", fps);
		CountTicks = 0;
	}
	//Move
	if ( MOVING )
	{
		MoveThink(lastTick - MoveStart);
	}
	else
	{
		switch(DIRECTION)
		{
			case 0:
				CurrentAnimation = 6;
				break;
			case 1:
				CurrentAnimation = 3;
				break;
			case 2:
				CurrentAnimation = 0;
				break;
			case 3:
				CurrentAnimation = 9;
				break;

		}
	}
	//Graphics
	EngineCoreAccess->ClearRenderList();
	//Enemies
	for ( int i = 0; i < 5; i++ )
	{
		if ( Enemies[i]->Think(PlayerPosition,MOVING,DIRECTION) )
		{
			Entitys[i + 1]->Active = true;
			Entitys[i + 1]->Position = *Enemies[i]->OnscreenPosition;
			if ( PlayerPosition->x == Enemies[i]->WorldPosition->x &&
				 PlayerPosition->y == Enemies[i]->WorldPosition->y )
			{
				KillPlayer();
				EngineCoreAccess->PlaySound(0);
				RefreshPosition();
			}
		}
		else
		{
			Entitys[i + 1]->Active = false;
			Entitys[i + 1]->Position.x = -200;
		}
	}
	SetPlayerAnimation();
	for ( int i = GAME_ENTITYS - 1; i >= 0; i--)
	{
		if ( Entitys[i]->Active )
		{
			EngineCoreAccess->AddEntityToRenderList(Entitys[i]);
		}
	}

	
}

void CGame_Core::SetPlayerAnimation()
{
	switch(CurrentAnimation)
	{
		case 0:
			Entitys[0]->SpriteID = 1;
			break;
		case 1:
			Entitys[0]->SpriteID = 8;
			break;
		case 2:
			Entitys[0]->SpriteID = 9;
			break;
		case 3:
			Entitys[0]->SpriteID = 10;
			break;
		case 4:
			Entitys[0]->SpriteID = 11;
			break;
		case 5:
			Entitys[0]->SpriteID = 12;
			break;
		case 6:
			Entitys[0]->SpriteID = 13;
			break;
		case 7:
			Entitys[0]->SpriteID = 14;
			break;
		case 8:
			Entitys[0]->SpriteID = 15;
			break;
		case 9:
			Entitys[0]->SpriteID = 16;
			break;
		case 10:
			Entitys[0]->SpriteID = 17;
			break;
		case 11:
			Entitys[0]->SpriteID = 18;
			break;
	}
}

int CGame_Core::ControlsMain( void )
{
	SDL_Event event;
	int ExitButtons = 0;
	while(SDL_PollEvent(&event))
	{
	 switch(event.type)
		{
			case SDL_JOYBUTTONDOWN:
				switch(event.jbutton.button)
				{
					case GP2X_BUTTON_UP:
						UP_PRESSED = true;
						break;
					case GP2X_BUTTON_DOWN:
						DOWN_PRESSED = true;
						break;
					case GP2X_BUTTON_LEFT:
						LEFT_PRESSED = true;
						break;
					case GP2X_BUTTON_RIGHT:
						RIGHT_PRESSED = true;
						break;
					case GP2X_BUTTON_X:

						break;
					case GP2X_BUTTON_START:
						START_PRESSED = true;
						break;
					case GP2X_BUTTON_L:
						LSHOULDER_PRESSED = true;
						break;
					case GP2X_BUTTON_R:
						RSHOULDER_PRESSED = true;
						break;
				}
				break;

			case SDL_JOYBUTTONUP:
				switch(event.jbutton.button)
				{
					case GP2X_BUTTON_UP:
						UP_PRESSED = false;
						break;
					case GP2X_BUTTON_DOWN:
						DOWN_PRESSED = false;
						break;
					case GP2X_BUTTON_LEFT:
						LEFT_PRESSED = false;
						break;
					case GP2X_BUTTON_RIGHT:
						RIGHT_PRESSED = false;
						break;
					case GP2X_BUTTON_START:
						START_PRESSED = false;
						break;
					case GP2X_BUTTON_L:
						LSHOULDER_PRESSED = false;
						break;
					case GP2X_BUTTON_R:
						RSHOULDER_PRESSED = false;
						break;
				}
				break;

			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						UP_PRESSED = false;
						break;
					case SDLK_DOWN:
						DOWN_PRESSED = false;
						break;
					case SDLK_LEFT:
						LEFT_PRESSED = false;
						break;
					case SDLK_RIGHT:
						RIGHT_PRESSED = false;
						EngineCoreAccess->PlaySound(0);
						break;
					case SDLK_F12:
						EngineCoreAccess->Engine_Running = false;
						break;
				}
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						UP_PRESSED = true;
						break;
					case SDLK_DOWN:
						DOWN_PRESSED = true;
						break;
					case SDLK_LEFT:
						LEFT_PRESSED = true;
						break;
					case SDLK_RIGHT:
						RIGHT_PRESSED = true;
						break;
				}
				break;
		}						
	}
	if ( LSHOULDER_PRESSED && RSHOULDER_PRESSED && START_PRESSED )
	{
		EngineCoreAccess->Engine_Running = false;
	}
	if ( UP_PRESSED )
	{
		Move(0);
	}
	if ( DOWN_PRESSED )
	{
		Move(2);
	}
	if ( LEFT_PRESSED )
	{
		Move(1);
	}
	if ( RIGHT_PRESSED )
	{
		Move(3);
	}
	return 0;
}
		
void CGame_Core::Move(int direction)
{
	bool NotBlocked = false;
	if ( !MOVING )
	{
		if ( direction == 0 )
		{
			if ( Grid->Byte_Grid[5][3] == '0')
			{
				PlayerPosition->y--;
				NotBlocked = true;
				CurrentAnimation = 7;//Start walking
			}
		}
		if ( direction == 1 )
		{
			if ( Grid->Byte_Grid[4][4] == '0')
			{
				PlayerPosition->x--;
				NotBlocked = true;
				CurrentAnimation = 4;//Start walking
			}
		}
		if ( direction == 2 )
		{
			if ( Grid->Byte_Grid[5][5] == '0')
			{
				PlayerPosition->y++;
				NotBlocked = true;
				CurrentAnimation = 1;//Start walking
			}
		}
		if ( direction == 3 )
		{
			if ( Grid->Byte_Grid[6][4] == '0')
			{
				PlayerPosition->x++;
				NotBlocked = true;
				CurrentAnimation = 10;//Start walking
			}
		}
		
	}
	if ( NotBlocked )
	{
		DIRECTION = direction;
		MOVING = true;
		MoveStart = lastTick;
	}
}

void CGame_Core::KillPlayer()
{
	PlayerPosition->x = 64;
	PlayerPosition->y = 64;
}

void CGame_Core::MoveThink(Uint32 frames)
{
	int distance = (32 * frames) / 250;//This works out to be the length of a frame over a half a second.
	if ( distance % 16 == 0 )
	{
		switch (CurrentAnimation)
		{
			case 1:
				CurrentAnimation = 2;
				break;
			case 2:
				CurrentAnimation = 1;
				break;
			case 4:
				CurrentAnimation = 5;
				break;
			case 5:
				CurrentAnimation = 4;
				break;
			case 7:
				CurrentAnimation = 8;
				break;
			case 8:
				CurrentAnimation = 7;
				break;
			case 10:
				CurrentAnimation = 11;
				break;
			case 11:
				CurrentAnimation = 10;
				break;
		}
	}
	if ( distance >= 33 )
	{
		//Ok we've done the move, reset the positions and assign new values
		distance = 0;
		RefreshPosition();
	}
	if ( DIRECTION == 0 )
	{
		EngineCoreAccess->SetOffset(0,distance);
	}
	if ( DIRECTION == 1 )
	{
		EngineCoreAccess->SetOffset(distance,0);
	}
	if ( DIRECTION == 2 )
	{
		EngineCoreAccess->SetOffset(0,-distance);
	}
	if ( DIRECTION == 3 )
	{
		EngineCoreAccess->SetOffset(-distance,0);
	}
}

void CGame_Core::RefreshPosition()
{
	MOVING = false;
	for (int i = 0; i < TILE_X_COUNT; i++ )
	{
		for ( int j = 0; j < TILE_Y_COUNT; j++)
		{
			Grid->Byte_Grid[i][j] = ByteMap->Byte_Grid[PlayerPosition->x - TILE_X_COUNT +i][PlayerPosition->y - TILE_Y_COUNT + j];
		}
	}
	printf("X = %i ,", PlayerPosition->x);
	printf("Y = %i \n", PlayerPosition->y);
}

SDL_Color CGame_Core::GetMapPixel(Bitmap* Map, int x, int y)
{
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	if ( x > 0 && x < 128 && y > 0 && y < 128 )
	{
		Uint32 col = 0;
		char* pPosition = ( char * ) Map->GetSurface()->pixels ;
		//offset by y
		pPosition += ( Map->GetSurface()->pitch * y ) ;
		//offset by x
		pPosition += ( Map->GetSurface()->format->BytesPerPixel * x ) ;
		//copy pixel data
		memcpy ( &col , pPosition , Map->GetSurface()->format->BytesPerPixel ) ;
		SDL_GetRGB ( col , Map->GetSurface()->format , &color.r , &color.g , &color.b ) ;
	}
	return color;
}

int CGame_Core::GetSpriteForColor(SDL_Color Color)
{
	if ( Color.r == 0 && Color.g == 255 && Color.b == 0 )
	{
		return 2;
	}
	if ( Color.r == 0 && Color.g == 0 && Color.b == 0 )
	{
		return 6;
	}
	if ( Color.r = 255 && Color.g == 0 && Color.b == 0 )
	{
		return 5;
	}
	if ( Color.r = 0 && Color.g == 0 && Color.b == 255 )
	{
		return 7;
	}
	return 3;
}

char CGame_Core::GetByteForColor(SDL_Color Color)
{
	if ( Color.r == 0 && Color.g == 255 && Color.b == 0 )
	{
		return '0';
	}
	if ( Color.r == 0 && Color.g == 0 && Color.b == 0 )
	{
		return '1';
	}
	if ( Color.r = 255 && Color.g == 0 && Color.b == 0 )
	{
		return '2';
	}
	if ( Color.r == 0 && Color.g == 0 && Color.b == 255 )
	{
		return '3';
	}
	return '1';
}

void CGame_Core::LoadByteMap()
{
	Bitmap* Map = new Bitmap("Map.bmp");
	for ( int i = 0; i < 128; i++ )
	{
		for ( int j = 0; j < 128; j++ )
		{
			//Convert the bitmap into a bytegrid
			ByteMap->Byte_Grid[i][j] = GetByteForColor(GetMapPixel(Map,i,j));
		}
	}
	SDL_FreeSurface(Map->LoadedImage);
}

