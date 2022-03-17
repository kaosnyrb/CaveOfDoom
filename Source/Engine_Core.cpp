#include "Engine_Core.h"

CEngine_Core::CEngine_Core()
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO);
	//SDL_ShowCursor(0);
	SDL_JoystickOpen(0);
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, 0);
	Menu = true; //Start the game in the menus
	lastTick = SDL_GetTicks();
	xOffset = 0;
	yOffset = 0;
	for ( int i = 0; i < TOTAL_BITMAPS;i++ )
	{
		Bitmaps[i] = 0;
	}
	for ( int i = 0; i < TOTAL_SPRITES;i++ )
	{
		Sprites[i] = 0;
	}
	for ( int i = 0; i < TOTAL_ENTITYS;i++ )
	{
		Entitys[i] = 0;
	}
	//Sound
	// Initialise audio
	SDL_AudioSpec *desiredAudioSpec;
	if (!(Audio_Spec = (SDL_AudioSpec*)malloc(sizeof(SDL_AudioSpec)))) throw "Audio buffer allocate failed";
	if (!(desiredAudioSpec = (SDL_AudioSpec*)malloc(sizeof(SDL_AudioSpec)))) throw "Audio buffer allocate failed";
	desiredAudioSpec->freq = 44100;
	desiredAudioSpec->format = AUDIO_S16;
	desiredAudioSpec->samples = 1024;
	desiredAudioSpec->channels = 1;
	desiredAudioSpec->callback = Sound::AudioCallback;
	desiredAudioSpec->userdata = 0;
	if (-1 == SDL_OpenAudio(desiredAudioSpec, Audio_Spec)) throw "SDL failed to open audio stream";
	free(desiredAudioSpec);
	SDL_PauseAudio(0);
	//init sound
	for ( int i = 0; i < TOTAL_SOUNDS;i++ )
	{
		Sounds[i] = new Sound();
	}
	
	Sounds[0]->LoadAndConvertSound("beep.wav",Audio_Spec,0); //memory saving
	//Sounds[1]->LoadAndConvertSound("music.wav",Audio_Spec,1);

	//Loading of assests
	Uint32 Key = SDL_MapRGB(screen->format,255,0,255);
	//Bitmaps[0] = new Bitmap("World.bmp");
	Bitmaps[1] = new Bitmap("Tiles.bmp",Key);
	
	//Sprites[0] = new Sprite(Bitmaps[0],MakeSDL_Rect(240,320,0,0));
	Sprites[1] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,0,106));//player down still
	Sprites[8] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,15,106));//player down 1
	Sprites[9] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,32,106));//player down 2

	Sprites[10] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,48,106));//player Left still
	Sprites[11] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,64,106));//player Left 1
	Sprites[12] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,80,106));//player Left 2

	Sprites[13] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,96,106));//player UP still
	Sprites[14] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,112,106));//player UP 1
	Sprites[15] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,128,106));//player UP 2

	Sprites[16] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,144,106));//player Right still
	Sprites[17] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,160,106));//player Right 1
	Sprites[18] = new Sprite(Bitmaps[1],MakeSDL_Rect(22,16,176,106));//player Right 2


	Sprites[2] = new Sprite(Bitmaps[1],MakeSDL_Rect(32,32,0,0));
	Sprites[3] = new Sprite(Bitmaps[1],MakeSDL_Rect(32,32,32,32));
	Sprites[4] = new Sprite(Bitmaps[1],MakeSDL_Rect(32,32,64,32));//Enemy
	Sprites[5] = new Sprite(Bitmaps[1],MakeSDL_Rect(32,32,64,0));//LAVA!!!
	Sprites[6] = new Sprite(Bitmaps[1],MakeSDL_Rect(32,32,0,32));//Bricks
	Sprites[7] = new Sprite(Bitmaps[1],MakeSDL_Rect(32,32,96,0));//Ice Ice baby

	Sprites[0] = new Sprite(Bitmaps[1],MakeSDL_Rect(48,127,128,0));
		
	Sprites[19] = new Sprite(Bitmaps[1],MakeSDL_Rect(48,110,130,48));//Title
	Sprites[20] = new Sprite(Bitmaps[1],MakeSDL_Rect(16,76,0,64));//New Game
	Sprites[21] = new Sprite(Bitmaps[1],MakeSDL_Rect(16,32,0,80));//Quit


	Engine_Running = true;
}

CEngine_Core::~CEngine_Core()
{
	SDL_CloseAudio();
	free(Audio_Spec);
	SDL_Quit();
}

void CEngine_Core::Main()
{
	SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
	SDL_Rect GridTemp = MakeSDL_Rect(32,32,0,0);
	//Draw Grid
	if ( !Menu )
	{
		for (int i = 0; i < GRIDX; i++ )
		{
			for ( int j = 0; j < GRIDY; j++)
			{
				GridTemp.x = i*32 - 32 + xOffset;
				GridTemp.y = j*32 - 32 + yOffset;
				SDL_BlitSurface(Sprites[GetIdForByte(Grid->Byte_Grid[i][j])]->GetSurface(), 
					&Sprites[GetIdForByte(Grid->Byte_Grid[i][j])]->GetTextureArea(),screen,&GridTemp);
			}
		}
	}
	//Draw Entitys
	for ( int i = TOTAL_ENTITYS - 1; i >= 0; i--)
	{
		if (  Entitys[i] != 0 )
		{
			if (Entitys[i]->SpriteID != 4)
			{
				SDL_Rect Temp = MakeSDL_Rect(Entitys[i]->SourceSprite->Height,Entitys[i]->SourceSprite->Width,
					Entitys[i]->Position.x,Entitys[i]->Position.y);
				SDL_BlitSurface(Entitys[i]->SourceSprite->GetSurface(), &Entitys[i]->SourceSprite->GetTextureArea(), screen,
					&Temp);
			}
			else
			{
				SDL_Rect Temp = MakeSDL_Rect(Entitys[i]->SourceSprite->Height,Entitys[i]->SourceSprite->Width,
					Entitys[i]->Position.x + xOffset,Entitys[i]->Position.y + yOffset);
				SDL_BlitSurface(Entitys[i]->SourceSprite->GetSurface(), &Entitys[i]->SourceSprite->GetTextureArea(), screen,
					&Temp);

			}
		}
	}
	SDL_Flip(screen);
}

void CEngine_Core::AddEntityToRenderList(Entity* pEntity)
{
	for ( int i = TOTAL_ENTITYS - 1; i >= 0; i--)
	{
		if ( Entitys[i] == 0 || !Entitys[i]->Active )
		{
			Entitys[i] = pEntity;
			Entitys[i]->SourceSprite = Sprites[pEntity->SpriteID];
			Entitys[i]->Active = true;
			return;
		}
	}
}

void CEngine_Core::ClearRenderList()
{
	for ( int i = TOTAL_ENTITYS - 1; i >= 0; i--)
	{
		if ( Entitys[i] != 0 )
		{
			Entitys[i] = 0;
		}
	}
}


SDL_Rect CEngine_Core::MakeSDL_Rect(int pH,int pW,int pX,int pY)
{
	SDL_Rect Temp;
	Temp.h = pH;
	Temp.w = pW;
	Temp.x = pX;
	Temp.y = pY;
	return Temp;
}

void CEngine_Core::PlaySound(int id)
{
	Sounds[id]->PlaySound();
}

int CEngine_Core::GetIdForByte(char pchar)
{
	if ( pchar == '0' )
	{
		return 2;
	}
	if ( pchar == '1' )
	{
		return 6;
	}
	if ( pchar == '2' )
	{
		return 5;
	}
	if ( pchar == '3' )
	{
		return 7;
	}
	if ( pchar == 'b')
	{
		return 3;
	}
	return 0;
}

