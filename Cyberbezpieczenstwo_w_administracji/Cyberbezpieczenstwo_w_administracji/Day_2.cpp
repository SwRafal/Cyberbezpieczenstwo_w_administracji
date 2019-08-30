#include "Day_2.h"

Day_2::Day_2()
{
	gm::Assets::LoadTexture("itGuy",IT_GUY_TEXTURE);
 	itGuy = new OfficeFriend(gm::Assets::getTexture("itGuy"));

	state = -1;

	init = false;
}

Day_2::~Day_2()
{
	
}


void Day_2::update(GameState *gs, sf::RenderWindow &win)
{
	if(!init)
	{
		time = gm::Core::getClock().getElapsedTime().asSeconds();

		sf::String s = L"Czeœæ";
		
		
		


		

		if(gm::Core::getClock().getElapsedTime().asSeconds() - time >= 3)
		{
			state = 0;
			init = true;
		}
	}

	

	switch (state)
	{
	case 0:
		
		itGuy->animate();
		

		break;
	}

	itGuy->animate();
}

void Day_2::draw(GameState *gs, sf::RenderWindow &win)
{
	itGuy->draw(win);

	win.display();
}
