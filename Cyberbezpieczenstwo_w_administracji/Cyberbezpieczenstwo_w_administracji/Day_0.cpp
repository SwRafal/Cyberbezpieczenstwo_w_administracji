#include "Day_0.h"
#include "GameState.h"

Day_0::Day_0()
{
	state = 0;
	showTextField = false;
	showButtons = false;
	part1Over = false;
}

void Day_0::update(GameState* gs)
{
	

	if(gs->day == 0)
	{
		
		if(showButtons)
		{
			gs->choice1->setPosition(gs->officeLady->chat.getPosition().x ,gs->officeLady->chat.getPosition().y + gs->officeLady->chat.getGlobalBounds().height);
			gs->choice2->setPosition(gs->choice1->background.getPosition().x + gs->choice1->background.getGlobalBounds().width ,gs->choice1->background.getPosition().y );
		}
		else
		{
			gs->choice1->setPosition(0,-300);
			gs->choice1->setPosition(0,-300);
		}

		if(showTextField)
		{
			gs->textField->setPosition(gs->officeLady->chat.getPosition().x,gs->officeLady->chat.getPosition().y + gs->officeLady->chat.getGlobalBounds().height);
		}
		else
			gs->textField->setPosition(0,-300);
	}


	if(!part1Over)
	{
	if(gs->day == 0)
	{
		

		if(gs->dayShowScreen->finished && state == 0)
		{
			gs->officeLady->show();
			state = 1;
		}

		if(gs->data->characterChoice != 1) //mag + haker
		{
			if(gs->officeLady->state == 2 && state == 1)
			{
				state = 2;
				gs->officeLady->setButtonInactive();
			}
			
			if(state == 2)
			{
				showButtons = true;
			
				if(gs->choice1->clicked(gm::Core::getWindow()))
				{
					showButtons = false;
					showTextField = true;
					state = 5;
					gs->officeLady->setButtonActive();
				}
				else if(gs->choice2->clicked(gm::Core::getWindow()))
				{
					state = 3;
					showButtons = false;
					gs->officeLady->nextLine();
					gs->popUpText->setBubblePosition(SCREEN_WIDTH / 2 - gs->popUpText->getGlobalBounds().width / 2,SCREEN_HEIGHT / 2 - gs->popUpText->getGlobalBounds().height / 2);
					gs->popUpText->showBubble();
					gs->time = gm::Core::getClock().getElapsedTime().asSeconds();
				}
			}

			if(state == 3)
			{
				if(gm::Core::getClock().getElapsedTime().asSeconds() - gs->time >= 5)
				{
					gs->popUpText->closeBubble();
					state = 5;
					showTextField = true;
				}
			}

			if(state == 5)
			{
				if(gm::Core::getEnteredChar() == 13 && gs->textField->getTextString().getSize() > 0)
				{
					gs->data->name = gs->textField->getTextString();
					

					state = 6;
					showTextField = false;
					gs->officeLady->nextLine();
					gs->officeLady->nextLine();
					sf::String s = L"Mi³o mi Ciê poznaæ ";
					s = s + gs->data->name + sf::String(L", wiele o Tobie s³ysza³am.");
					gs->officeLady->text.setTextString(s);
					gs->officeLady->setButtonActive();
				}
			}
		/*
		 *state:
		 *0- znika od razu
		 *1- po pierwszym kliknieciu w strzalke znika
		 *2- wybor z imieniem
		 *3- ( wybor z rodo) kolezanka mowi dalej
		 *4 - okienko na ekran
		 *5- wpisz imie
		 *6+ - ostateczne co mowi baba 
		 */
		}
	}
	}
		if(gs->data->characterChoice == 1 && gs->officeLady->state == 4)
			part1Over = true;
		if((gs->data->characterChoice == 2 || gs->data->characterChoice == 3) && gs->officeLady->state == 6)
			part1Over = true;

	if(part1Over)
	{
		
	}
	
	
}