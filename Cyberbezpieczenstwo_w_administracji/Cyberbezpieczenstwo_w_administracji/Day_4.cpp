#include "Day_4.h"
#include "GameState.h"

Day_4::Day_4()
{
	showButtons = false;
	state = -1;

	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->setBubblePosition(0, -300);

	if (gm::Assets::getTexture("boss") == nullptr)
	{
		gm::Assets::LoadTexture("boss", BOSS_TEXTURE);

		if (gm::Assets::getTexture("boss") == nullptr)
			error_win_close();
	}
	boss = new OfficeApplicant(gm::Assets::getTexture("boss"));

	itGuy = new OfficeApplicant(gm::Assets::getTexture("itGuy"));
	itGuy->move(0,10);
	offset = 20;
	itGuy->chat.move(offset,0);
	itGuy->text.move(offset,0);
	itGuy->button.move(offset,0);
	itGuy->img.move(offset,0);

	//quest1
	gm::Assets::LoadTexture("gazeta",GAZETA);
	newspaper.setTexture(*gm::Assets::getTexture("gazeta"));
	newspaper.setPosition(400,10);

	gm::Assets::LoadTexture("petent1", PETENT1);
	petent1 = new OfficeApplicant(gm::Assets::getTexture("petent1"));
	petent1->move(0,2);
	petent1->moveChatBox(30,0);
	
	gm::Assets::LoadTexture("dowod1", DOWOD1);
	dowod1.setTexture(*gm::Assets::getTexture("dowod1"));
	//dowod1.setPosition(285,133);

	callIn = false;
	drawDowod = false;
}

Day_4::~Day_4()
{
	
}

void Day_4::update(GameState* gs, sf::RenderWindow& win)
{
	if(showButtons)
	{
		if(state == 0)
		{
			
		}
		else
		{
			gs->choice1->setPosition(SCREEN_WIDTH / 2 - gs->choice1->background.getGlobalBounds().width - 5,SCREEN_HEIGHT * 0.6);
			gs->choice2->setPosition(SCREEN_WIDTH / 2 + 5,SCREEN_HEIGHT * 0.6);
		}
			
	}
	else
	{
		gs->choice1->setPosition(0,-300);
		gs->choice2->setPosition(0,-300);
	}

	if(!gs->dayShowScreen->finished)
		return;

	itGuy->animate();
	boss->animate();
	petent1->animate();

	switch (state)
	{
	case -1: //init
		gs->openedbook->setInfoL(L"Minimalizacja danych osobowych � tylko dane niezb�dne do celu przetwarzania");
		gs->xero->setPosition(XERO_POS_X, XERO_POS_Y);
		gs->card->setPosition( 830,500);
		gs->openedcomputer->getLogin() = gs->data->login;
		gs->openedcomputer->getPassword() = gs->data->password;
		gs->cardReader->hidden = false;
		gs->cardReader->update();
		state++;
		break;
	case 0: //wypij kawe
		if (gs->coffee->update_drunk(win))
		{
			gs->battery->setActivation(true);
			coffeeClicked = true;
			state = 2;
			gs->book->setFillColor(sf::Color(230, 230, 230));
		}
		else if (gs->book->clicked(win) || gs->bell->clicked(win) || gs->bin->clicked(win) || gs->no_stamp->clicked(win) || gs->yes_stamp->clicked(win) || gs->computer->clicked(win) || gs->card->clicked(win))
		{
			thought->changeText(L"Nie �pij w pracy!");
			gs->data->nagany++;
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			thought->showBubble();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			state++;
		}
		thought->animate();
		break;
	case 1: //nie spij w pracy
		thought->animate();
		if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 0;
		}
		break;
	case 2: //read book
		thought->animate();
		gs->book->update(win);
		gs->openedbook->update(win);
		if(gs->book->isOpened())
			bookOpened = true;
		if(bookOpened && !gs->book->isOpened())
			state++;
		break;
	case 3:
		gs->card->update(win);
		gs->cardReader->update();
		if(gs->cardReader->isCardInside())
		{
			gs->computer->update(win);
			gs->openedcomputer->update(win);
			if(gs->computer->powerOn)
			{
				if(gs->openedcomputer->getState() == OpenPC::DESKTOP)
				{
					gs->computer->close();
					state++;
				}
			}
		}
		break;
	case 4: //gosc z it
		itGuy->setButtonActive();
		itGuy->state = 0;
		itGuy->text.setTextString(L"Hej widzia�e� dzisiejsz� gazet�?");
		itGuy->addToQueue(L" ");
		itGuy->show();
		state++;
		break;
	case 5: //pokaz gazete
		if(itGuy->state == 1)
		{
			showNewspaper = true;
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				showNewspaper = false;
				itGuy->state = 0;
				itGuy->text.setTextString(L"Ooooo widz�, �e pami�� naszego kombajnu jest totalnie zapchana");
				itGuy->addToQueue(L"woooaaa!!! Zeskanowa�e� wczoraj ca�� baz� pracownik�w Ministerstwa?");
				itGuy->addToQueue(L"No tak, szef pewnie nie powiedzia� ci, �e po zako�czonym skanowaniu,");
				itGuy->addToQueue(L"drukowaniu czy kserowaniu trzeba czy�ci� pami�� takiego urz�dzenia?");
				itGuy->addToQueue(L"Nie? To w jego stylu� przecie� ''Drukarka to nie komputer''");
				itGuy->addToQueue(L"''Nikt przez nas przez ni� nie zaatakuje.''");
				itGuy->addToQueue(L"Na przysz�o�� pami�taj, �e\n drukarka pod��czona do sieci");
				itGuy->addToQueue(L"jest najs�abszym ogniwem obrony naszych urz�d�w");
				itGuy->addToQueue(L"G�ra �a�uje nam funduszy na prawid�owe ich zabezpieczenie");
				itGuy->addToQueue(L"Postaraj si�, �eby czy�ci� jej pami�� zanim p�jdziesz do domu");
				itGuy->addToQueue(L"Mieli�my szcz�cie, �e tym razem nie zaatakowano nas");
				itGuy->addToQueue(L"OK, zrobi�em co mia�em zrobi�.");
				itGuy->addToQueue(L"Masz zainstalowny nowy system pozwalaj�cy sprawniej zaprasza� petent�w. Powodzenia!");
				itGuy->addToQueue(L" ");
				state++;
			}
			
		}
		break;
	case 6: //monolog itguya
		if(itGuy->state == 13)
		{
			itGuy->hide();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			thought->changeText(L"By wezwa� interesanta, naci�nij dzwonek");
			thought->showBubble();
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			state++;
		}
		break;
	case 7: //info bubble
		thought->animate();
		//thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state++;
		}
		break;
	case 8:
		thought->animate();
		if(thought->hidden)
			{
				state++;
			}
		break;
	case 9: //1 petent
		
		if(callIn)
		{
			petent1->setButtonInactive();
			petent1->text.setTextString(L"Dzie� dobry, chcia�bym si� dowiedzie� czy moje prawo jazdy ju� jest gotowe do odbioru?");
			petent1->show();
			gs->choice1->setText(L"Prosz� o okazanie\ndowodu osobistego");
			gs->choice2->setText(L"Prosze o podanie imienia,\nnazwiska i numeru PESEL");
			showButtons = true;
			state++;
		}
		break;
	case 10:
		if(gs->choice1->clicked(win))
		{
			drawDowod = true;
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			petent1->text.setTextString(L"Nazywam si� Jan Kowalski, numer PESEL to 93030215201");
			gs->choice1->setText(L"Dokument jest gotowy do odbioru,\nprosz� o okazanie dowodu osobistego");
			gs->choice2->setText(L"Dokument jest gotowy do odbioru");
			state = 14;
		}
		break;
	case 11:
		gs->choice1->setText(L"Wydaj prawo jazdy");
		gs->choice2->setText(L"Skseruj dow�d i wydaj prawo jazdy");
		if(gs->choice1->clicked(win))
		{
			showButtons = false;
			drawDowod = false;
			dowod1.setPosition(SCREEN_WIDTH,SCREEN_HEIGHT);
			petent1->text.setTextString(L"Dzi�kuj�");
			petent1->addToQueue(L" ");
			quest1completed = true;
			petent1->setButtonActive();
			petent1->state = 0;
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			showButtons = false;
			drawDowod = false;
			dowod1.setPosition(SCREEN_WIDTH,SCREEN_HEIGHT);
			petent1->text.setTextString(L"Dzi�kuj�");
			petent1->addToQueue(L" ");
			petent1->setButtonActive();
			petent1->state = 0;

			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			thought->changeText(L"Kserowanie dowodu nie jest niezb�dne do wykonania zadania, a nara�a urz�d na wyciek danych");
			thought->showBubble();

			gs->data->nagany++;
			state = 13;
			
		}
		break;
	case 12:
		if(petent1->state == 1)
		{
			petent1->hide();
			
			//go to quest 2
		}
		break;
	case 13:
		thought->animate();
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			thought->closeBubble();

		if(thought->hidden)
			state = 12;
		break;
	case 14:
		if(gs->choice1->clicked(win))
		{
			drawDowod = true;
			state = 11;
		}
		if(gs->choice2->clicked(win))
		{
			showButtons = false;
			gs->gameover(L"Przekaza�e� dokument zawierajacy dane osobowe (wyciek danych) osobie, kt�rej uprawnienia do otrzymania tych danych nie zweryfikowa�e�.\nFa�szywy Jan Kowalski pos�u�y� si� prawem jazdy do wyp�aty got�wki w banku prawowitego w�a�ciciela.\nZostajesz zwolniony dyscyplinarnie w trybie natychmiastowym");
		}
		break;
	}

}

void Day_4::draw(GameState* gs, sf::RenderWindow& win)
{
	thought->draw(win);
	itGuy->draw(win);
	boss->draw(win);
	petent1->draw(win);

	

	if(drawDowod)
	{
		win.draw(dowod1);
	}

	if(showNewspaper)
		win.draw(newspaper);

	gs->choice1->draw(win);
	gs->choice2->draw(win);

	win.display();
}

