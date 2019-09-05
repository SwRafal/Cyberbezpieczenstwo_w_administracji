#include "Day_2.h"
#include "GameState.h"

Day_2::Day_2()
{
	gm::Assets::LoadTexture("itGuy",IT_GUY_TEXTURE);
	gm::Assets::LoadTexture("itGuyHand", IT_GUY_HAND_TEXTURE);
 	itGuy = new OfficeApplicant(gm::Assets::getTexture("itGuy"));
	itGuy->move(0,10);
	offset = 20;
	itGuy->chat.move(offset,0);
	itGuy->text.move(offset,0);
	itGuy->button.move(offset,0);
	itGuy->img.move(offset,0);

	gm::Assets::LoadTexture("boss",BOSS_TEXTURE);
	boss = new OfficeApplicant(gm::Assets::getTexture("boss"));
	offset = 60;
	boss->chat.move(offset,0);
	boss->text.move(offset,0);
	boss->button.move(offset,0);
	boss->img.move(offset,0);
	

	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->changeText(L"Nie �pij w pracy!!!");
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
		

		sf::String s = L"Cze�� ";
		s = s + gs->data->name + "!";

		itGuy->text.setTextString(s);
		itGuy->addToQueue(L"W�a�nie sko�czyli�my instalacj� potrzebnego ci oprogramowania. Jeste� ju� zalogowany na swoje konto.");
		itGuy->addToQueue(L"Od teraz do wszystkich wewn�trznych serwis�w Ministerstwa, wymagaj�cych has�a u�ywasz menad�era hase�.");
		itGuy->addToQueue(L"Ustawione przez ciebie wczoraj has�o, jest has�em do menad�era.");
		itGuy->addToQueue(L"Mo�esz zaczyna� prac�. \nMi�ego dnia.");
		itGuy->addToQueue(L" ");
		
		gs->openedbook->setInfoR(L"2 Uwierzytelnianie dwusk�adnikowe.");

		s = L"Witaj ";
		s = s + gs->data->name + "!";
		boss->text.setTextString(s);
		boss->addToQueue(L"Nasze Ministerstwo bierze udzia� w konkursie na najbezpieczniejsze ministerstwo �wiata.");
		boss->addToQueue(L"Od dzi� ka�de logowanie musi by� dwusk�adnikowe. Dalsze instrukcje w emailu.");
		boss->addToQueue(L" ");
		boss->state = 0;

		boss->move(0,11);

		s = gs->data->name +L": co si� sta�o?";
		gs->officeLady->text.setTextString(s);
		gs->officeLady->addToQueue(L"Kole�anka : Dosta�am nagan� za zapisywanie hase� na kartkach. Jeszcze jedna wtopa i wylatuj�.");
		gs->officeLady->addToQueue(L" ");
		gs->officeLady->state = 0;

		

		
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

	

	switch (state)
	{
	case 0: //gosc z it wbija
		itGuy->animate();

		
		if(itGuy->state == 5)
			itGuy->hide();

		if(itGuy->getPosition().x == 1390)
			state = 1;
		

		break;
	case 1: //drink coffee
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
	case 2: //nie spij w pracy
		thought->animate();
		if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 1;
		}
		break;
	case 3: //read book
		gs->book->update(win);
		gs->openedbook->update(win);

		if(gs->book->isOpened())
			bookOpened = true;

		
		if(bookOpened && !gs->book->isOpened())
			state++;

		break;
	case 4: //wpada szefu
		boss->show();
		state++;
		break;
	case 5:
		boss->animate();
		if(boss->state == 3)
			boss->hide();

		if(boss->getPosition().x == 1390)
		{
			state++;
			gs->officeLady->show();
		}
		break;
	case 6: //wpada ziomalka
		gs->officeLady->animate();
		if(gs->officeLady->state == 2)
			gs->officeLady->hide();
		if(gs->officeLady->getPosition().x >= 1390)
			state++;
		break;
	case 7: //wpada mail z it
		gs->computer->open();
		gs->openedcomputer->newMail(L"Silne uwierzytelnianie",L"IT@mdsw.gov.pl",L"Ochrona poufno�ci danych jest naszym priorytetem. Musimy zastosowa� co najmniej dwa elementy nale��ce do kategorii: \n1 Wiedza (czyli co� o czym wiesz tylko Ty). \n2 Posiadanie (co� co tylko Ty posiadasz). \n3 Cechy charakterystyczne u�ytkownika. \nElementy te s� integraln� cz�ci� uwierzytelnienia - Naruszenie jednego z nich nie os�abia ochrony gwarantowanej przez pozosta�e. \nWiedz� o danych logowania ju� masz. \nPrywatnie mo�esz wybra� z jakiego urz�dzenia dodatkowego chcesz korzysta�: SMS, TOKEN, LISTA HASE� (AKA ZDRAPKA), Generator hase� jednorazowych w twoim telefonie, s�u�bowym, Karta kryptograficzna, Odcisk palca. \nAle my w ministerstwie wybrali�my za ciebie. Otrzymujesz kart� s�u�bow� � musisz ni� potwierdza� ka�de logowanie do systemu. Dbaj o ni�. ");
		gs->openedcomputer->setState(OpenPC::MAIL);
		state++;
		break;
	case 8: //zamykanie kompa
		if(gs->openedcomputer->getState() != OpenPC::MAIL)
		{
			gs->computer->close();
			state++;
		}
		break;
	case 9: //gosc it init
		delete itGuy;
		itGuy = new OfficeApplicant(gm::Assets::getTexture("itGuyHand"));
		itGuy->move(0,10);
		offset = 70;
		itGuy->chat.move(offset,0);
		itGuy->text.move(offset,0);
		itGuy->button.move(offset,0);
		itGuy->img.move(offset,0);
		itGuy->state = 0;
		itGuy->text.setTextString(L"Prosz�, oto twoja karta. Pilnuj jej nale�ycie.");
		itGuy->addToQueue(L" ");
		itGuy->show();
		state++;
		break;
	case 10:
		itGuy->animate();
		
		gs->card->setPosition(itGuy->getPosition().x - 45,290);
		if(itGuy->state > 0)
		{
			itGuy->hide();
			state++;
		}
		break;
	case 11:
		
		
		if(itGuy->getPosition().x >= 1390)
			state++;

		itGuy->animate();
		break;
	case 12:
		//pojawia sie karta i czytnik;
		
		
		break;
	case 13:
		break;
	}

	
}

void Day_2::draw(GameState *gs, sf::RenderWindow &win)
{
	itGuy->draw(win);
	thought->draw(win);
	boss->draw(win);

	if(state== 10 || state == 11)
		win.draw(*gs->card);

	win.display();
}
