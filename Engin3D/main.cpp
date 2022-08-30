
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include "Game\Game.h"
#include "Utility/Utils.h"



#ifdef _WIN32
int WINAPI WinMain(	HINSTANCE Instance,		// Current Instance Handler 
					HINSTANCE PrevInstance,	// Previous Instance
					LPSTR CmdLine,			// Command Line Parameters
					int CmdShow)			// Window Show State
#else
int main(int argc, char **argv)
#endif
{

	Game::Get().Init();

	unsigned long lastTime = GetMiliSeconds();	//timeGetTime();

	while (!Game::Get().HasFinished())
	{
		// Calculate the time in seconds
		unsigned long actualTime = GetMiliSeconds();//timeGetTime();
		float TimeStep = ((float)(actualTime - lastTime) / 1000.0f);

		lastTime = actualTime;

		Game::Get().Update(TimeStep);

		Game::Get().Render();
	}
	
	Game::Get().Deinit();

	return 0;
}