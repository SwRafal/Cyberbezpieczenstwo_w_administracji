#include "Day_1.h"
#include "GameState.h"

Day_1::Day_1()
{
	state = 0;

	//Quest 1
	coffee_clicked = false;
	open_book = false;
	close_book = false;
	//Quest 2
	click_telephone = false;
	finish_telephone = false;
	finish_thought = false;
	choose_user = false;
	log_in = false;
	finish_dialog = false;
	click_mobile = false;
	put_mobile = false;
	change_login = false;
	change_password = false;
	remember_password = false;
	write_down_password = false;
	login_wifi = false;
	//Quest 4
	click_email = false;
	refused_email = false;
}

Day_1::~Day_1()
{
	
}

void Day_1::update(GameState *gs, sf::RenderWindow &win)
{
	switch (state)
	{
	case 0://Drink coffee

		gs->eyelids->update();
		if (gs->coffee->update_drunk(win))
		{
			gs->battery->setActivation(true);
			coffee_clicked = true;
			state++;
			gs->book->setFillColor(sf::Color(230, 230, 230));
			gs->eyelids->open();
		}
		else if (gs->book->clicked(win) || gs->bell->clicked(win) || gs->bin->clicked(win) || gs->no_stamp->clicked(win) || gs->yes_stamp->clicked(win))
		{
			gs->eyelids->increaseLvl();
		}

		if (gs->eyelids->getLvl() == FULL_CLOSED_EYES)
			std::cout << "PRZEGRALES";//Przegrana


		break;
	case 1://Open book

		if (gs->book->clicked(win))
		{
			gs->book->open();
			open_book = true;
			state++;
		}

		break;
	case 2://Close book

		if (!gs->book->isOpened())
		{
			close_book = true;
			state++;

			gs->phone->call();
		}

		break;
	case 3://Click telephone

		gs->phone->update(win);
		if (gs->phone->pickedUp)
		{
			click_telephone = true;
			state++;
		}

		break;
	case 4://Finish telephone

		gs->phone->update(win);

		break;
	case 5://Finish thought



		break;
	case 6://Choose user



		break;
	case 7://Login



		break;
	case 8://Finish dialog



		break;
	case 9:



		break;
	case 10:



		break;
	case 11:



		break;
	case 12:



		break;
	case 13:



		break;
	case 14:



		break;
	case 15:



		break;
	case 16:



		break;
	default:
		break;
	}
}

void Day_1::draw(GameState *gs, sf::RenderWindow &win)
{
	gs->eyelids->draw(win);

	win.display();
}