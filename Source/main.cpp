#include <stdio.h>
#include "Engine_Core.h"
#include "Game_Core.h"
#include "Menu_Core.h"

int main(int argc, char* argv[]) 
{
	printf("Hello, world\n");
	CEngine_Core* Engine = new CEngine_Core();
	CMenu_Core* Menus = new CMenu_Core(Engine);
	CGame_Core* Game = new CGame_Core(Engine);
	while(Engine->Engine_Running)
	{
		Engine->Main();
		if ( Engine->Menu )
		{
			Menus->Main();
		}
		else
		{
			Game->Main();
		}
	}
	return 0;
}
