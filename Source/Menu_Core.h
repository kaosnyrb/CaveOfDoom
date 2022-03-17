#pragma once

#include "Engine_Core.h"

class CMenu_Core
{
	public:
	CMenu_Core(CEngine_Core*);
	~CMenu_Core();
	void Main();
	private:
	CEngine_Core* EngineCoreAccess;
	util_bytegrid* BlankGrid;
	Entity* Credits;
	Entity* Title;
	Entity* NewGame;
	Entity* Quit;
	Entity* Selector;
	bool ShownCredits;
	int Selection;
	Uint32 timer;
	void RunSelection();
};