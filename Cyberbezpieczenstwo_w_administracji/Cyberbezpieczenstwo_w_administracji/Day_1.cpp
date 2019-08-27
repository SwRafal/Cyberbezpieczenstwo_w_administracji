#include "Day_1.h"
#include "GameState.h"

Day_1::Day_1()
{
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

void Day_1::update(GameState *gs, sf::RenderWindow &win)
{
	if (gs->battery->getActivation())
	{
		if (gs->coffee->update_drunk(win))
			gs->battery->setActivation(true);
		else if (gs->book->clicked(win) || gs->bell->clicked(win) || gs->bin->clicked(win) || gs->no_stamp->clicked(win) || gs->yes_stamp->clicked(win))
			gs->closed_eyes_level++;

		if (gs->closed_eyes_level == FULL_CLOSED_EYES)
			std::cout << "PRZEGRALES";//Przegrana
	}
	else
	{
		gs->book->setFillColor(sf::Color(230, 230, 230));
		gs->book->update(win);
	}
}