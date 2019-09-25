#include <iostream>
#include "Engine/Engine.h"
#include "Game.h"
#include "Definitions.h"
#include "SplashScreen.h"
#include <windows.h>

int main()
{
	HWND hWnd = GetConsoleWindow(); 
	ShowWindow( hWnd, SW_HIDE );

	srand(time(nullptr));

	showSplashScreen();

	gm::Game game;

	return EXIT_SUCCESS;
}
