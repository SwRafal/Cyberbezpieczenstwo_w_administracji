#include <iostream>
#include "Engine/Engine.h"
#include "Game.h"
#include "Definitions.h"
#include "SplashScreen.h"

int main()
{
	srand(time(nullptr));

	showSplashScreen();

	gm::Game game;

	return EXIT_SUCCESS;
}
