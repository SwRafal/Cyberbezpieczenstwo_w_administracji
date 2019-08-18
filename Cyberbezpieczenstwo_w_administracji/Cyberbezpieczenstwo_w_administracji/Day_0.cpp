#include "Day_0.h"
#include "Engine/Core.h"
#include "GameState.h"

Day_0::Day_0()
{
	state = 0;
	showTextField = false;
}

void Day_0::update(GameState* gs)
{
	if(gs->day == 0)
	{
		if(gs->dayShowScreen->finished)
			gs->officeLady->show();

		if(gs->data->characterChoice != 1) //mag + haker
		{
			if(gs->officeLady->state == 2)
			{
				state = 2;
				if(gs->choice1->clicked(gm::Core::getWindow()))
				{
					
				}
				if(gs->choice2->clicked(gm::Core::getWindow()))
				{
					state = 3;
					gs->officeLady->nextLine();
				}
			if(gs->officeLady->state == 3)
			{
				gs->popUpText->showBubble();
				gs->time = gm::Core::getClock().getElapsedTime().asSeconds();
				state = 4;
			}
			
			if(gm::Core::getClock().getElapsedTime().asSeconds() - gs->time >= 5)
			{
				gs->popUpText->closeBubble();
				state = 5;
				showTextField = true;
			}
			if(showTextField)
			{
				//pokaz okienko
			}


		}


		if(gs->officeLady->state == 3)
		{
			
		}
			if(gs->officeLady->state == 3)
			{
				std::cout << "wpisz imie";
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