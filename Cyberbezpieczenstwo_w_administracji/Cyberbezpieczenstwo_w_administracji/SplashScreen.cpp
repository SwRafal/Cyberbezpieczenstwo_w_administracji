#include "SplashScreen.h"

void showSplashScreen()
{
	sf::Texture splashTex;
	sf::Sprite SplashSprite;
	sf::Clock timer;
	sf::RenderWindow splashWin;

	splashTex.loadFromFile(SPLASH_STATE_BACKGROUND_FILEPATH);
	SplashSprite.setTexture(splashTex);
	splashWin.create(sf::VideoMode(SPLASH_STATE_WINDOW_WIDTH, SPLASH_STATE_WINDOW_HEIGHT), "Splash", sf::Style::None);

	splashWin.draw(SplashSprite);
	splashWin.display();

	while(splashWin.isOpen())
	{
		sf::Event event;

		while (splashWin.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				splashWin.close();
			}
		}

		if (timer.getElapsedTime().asSeconds() > SPLASH_STATE_SHOWTIME)
			splashWin.close();

		

	}
}