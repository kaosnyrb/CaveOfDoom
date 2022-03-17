#include "Menu_Core.h"

CMenu_Core::CMenu_Core(CEngine_Core* EngineHandle)
{
	EngineCoreAccess = EngineHandle;
	Credits = new Entity(0,util_vector2d(100,90));
	Title = new Entity(19,util_vector2d(100,60));
	NewGame= new Entity(20,util_vector2d(100,150));
	Quit = new Entity(21,util_vector2d(100,175));
	Selector = new Entity(16,util_vector2d(75,150));
	ShownCredits = false;
	Selection = 0;
}

void CMenu_Core::Main()
{
	EngineCoreAccess->ClearRenderList();
	if ( !ShownCredits )
	{
		EngineCoreAccess->AddEntityToRenderList(Credits);
		timer = SDL_GetTicks();
		if ( timer > 3000 )
		{
			ShownCredits = true;
			//
		}
	}
	if ( ShownCredits )
	{
		//Now to the main menu
		EngineCoreAccess->AddEntityToRenderList(Title);
		EngineCoreAccess->AddEntityToRenderList(NewGame);
		EngineCoreAccess->AddEntityToRenderList(Quit);
		EngineCoreAccess->AddEntityToRenderList(Selector);
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
					Selection = 0;
					break;
				case GP2X_BUTTON_DOWN:
					Selection = 1;
					break;
				case GP2X_BUTTON_X:
					RunSelection();
					break;
				case GP2X_BUTTON_START:
					RunSelection();
					break;
				}
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_UP:
					Selection = 0;
					break;
				case SDLK_DOWN:
					Selection = 1;
					break;
				case SDLK_RETURN:
					RunSelection();
					break;
				}
				break;
			}						
		}
		if ( Selection == 0 )
		{
			Selector->Position = util_vector2d(75,150);
		}
		else
		{
			Selector->Position = util_vector2d(75,175);
		}
	}

}

void CMenu_Core::RunSelection()
{
	if ( Selection == 0 )
	{
		EngineCoreAccess->Menu = false;
	}
	else
	{
		EngineCoreAccess->Engine_Running = false;
	}
}