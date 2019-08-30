#include "Day_2.h"
#include "GameState.h"

Day_2::Day_2()
{
	gm::Assets::LoadTexture("itGuy",IT_GUY_TEXTURE);
 	itGuy = new OfficeFriend(gm::Assets::getTexture("itGuy"));

	gm::Assets::LoadTexture("boss",BOSS_TEXTURE);
	boss = new OfficeApplicant(gm::Assets::getTexture("boss"));

	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->changeText(L"Nie œpij w pracy!!!");
	thought->setBubblePosition(0,-300);
	

	state = -1;

	init = false;
	initDelay = false;

	coffeeClicked = false;
	bookOpened = false;
}

Day_2::~Day_2()
{
	
}


void Day_2::update(GameState *gs, sf::RenderWindow &win)
{

	if(!init)
	{
		gs->coffee->reset();

		time = gm::Core::getClock().getElapsedTime().asSeconds();
		

		sf::String s = L"Czeœæ ";
		s = s + gs->data->name + "!";

		itGuy->text.setTextString(s);
		itGuy->addToQueue(L"W³aœnie skoñczyliœmy instalacjê potrzebnego ci oprogramowania. Jesteœ ju¿ zalogowany na swoje konto.");
		itGuy->addToQueue(L"Od teraz do wszystkich wewnêtrznych serwisów Ministerstwa, wymagaj¹cych has³a u¿ywasz menad¿era hase³.");
		itGuy->addToQueue(L"Ustawione przez ciebie wczoraj has³o, jest has³em do menad¿era.");
		itGuy->addToQueue(L"Mo¿esz zaczynaæ pracê. \nMi³ego dnia.");
		itGuy->addToQueue(L" ");
		
		gs->openedbook->setInfoR(L"2 Uwierzytelnianie dwusk³adnikowe.");

		s = L"Witaj ";
		s = s + gs->data->name + "!";
		boss->text.setTextString(s);
		boss->addToQueue(L"Nasze Ministerstwo bierze udzia³ w konkursie na najbezpieczniejsze ministerstwo œwiata.");
		boss->addToQueue(L"Od dziœ ka¿de logowanie musi byæ dwusk³adnikowe. Dalsze instrukcje w emailu.");
		boss->addToQueue(L" ");
		boss->state = 0;

		boss->move(0,11);

		
		init = true;
	}

	if(!initDelay)
	{
		if(gm::Core::getClock().getElapsedTime().asSeconds() - time >= 5)
		{
			state = 0;
			initDelay = true;

			itGuy->show();
		}
	}

	std::cout << state << std::endl;

	switch (state)
	{
	case 0:
		
		itGuy->animate();

		
		if(itGuy->state == 5)
			itGuy->hide();

		if(itGuy->getPosition().x == 1390)
			state = 1;
		

		break;
	case 1:
		
		if (gs->coffee->update_drunk(win))
		{
			gs->battery->setActivation(true);
			coffeeClicked = true;
			state = 3;
			gs->book->setFillColor(sf::Color(230, 230, 230));
		}
		else if (gs->book->clicked(win) || gs->bell->clicked(win) || gs->bin->clicked(win) || gs->no_stamp->clicked(win) || gs->yes_stamp->clicked(win) || gs->computer->clicked(win))
		{
			gs->data->nagany++;
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			thought->showBubble();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			state++;
		}
		thought->animate();
		break;
	case 2:
		thought->animate();
		if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 1;
		}
		break;
	case 3:
		gs->book->update(win);
		gs->openedbook->update(win);

		if(gs->book->isOpened())
			bookOpened = true;

		
		if(bookOpened && !gs->book->isOpened())
			state++;
		
			
		std::cout << std::endl << "book opened: " << bookOpened << "book isopened: " << gs->book->isOpened() << std::endl;
		

		break;
	case 4:
		boss->show();
		state++;
		break;
	case 5:
		boss->animate();
		if(boss->state == 3)
			boss->hide();

		if(boss->getPosition().x == 1390)
			state++;
		break;
	}

	
}

void Day_2::draw(GameState *gs, sf::RenderWindow &win)
{
	itGuy->draw(win);
	thought->draw(win);
	boss->draw(win);

	win.display();
}
