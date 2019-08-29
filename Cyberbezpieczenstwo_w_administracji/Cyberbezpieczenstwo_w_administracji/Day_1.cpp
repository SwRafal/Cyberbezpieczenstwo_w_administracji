#include "Day_1.h"
#include "GameState.h"

Day_1::Day_1()
{
	state = 0;
	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->changeText("Hmmm... Takie informacje przez telefon? To niezbyt bezpieczne...");
	thought->setBubblePosition(0,-300);

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

	//Initialize
}

Day_1::~Day_1()
{
	delete thought;
	thought = nullptr;
}

void Day_1::update(GameState *gs, sf::RenderWindow &win)
{
	if (gs->lost)
	{
		if (gm::Core::getClock().getElapsedTime().asMilliseconds() > gs->info_time)
		{
			gs->lost = false;
			gs->initialized = false;
			delete gs->gamelost_info;
			gs->gamelost_info = nullptr;
		}
	}
	else
	{
		switch (state)
		{
		case 0://Drink coffee

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
			{
				gs->lost = true;
				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
				gs->gamelost_info = new sf::Text;
				gs->gamelost_info->setFont(*gm::Assets::getFont());
				gs->gamelost_info->setString(L"Zasn¹³eœ w pracy!\nPamiêtaj o kawie!");
				gs->gamelost_info->setCharacterSize(48);
				sf::Vector2f info_pos;
				info_pos.x = SCREEN_WIDTH / 2 - (gs->gamelost_info->getLocalBounds().left + gs->gamelost_info->getLocalBounds().width) / 2;
				info_pos.y = SCREEN_HEIGHT / 2 - (gs->gamelost_info->getLocalBounds().top + gs->gamelost_info->getLocalBounds().height) / 2;
				gs->gamelost_info->setPosition(sf::Vector2f(info_pos));
			}

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
			if (!gs->phone->pickedUp)
			{
				finish_telephone = true;
				thought->setBubblePosition(300, 400);
				thought->showBubble();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
				state++;
			}

			break;
		case 5://Finish thought

			thought->animate();
			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				finish_thought = true;
				thought->closeBubble();
				thought->setBubblePosition(0, -300);
				state++;
			}

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
}

void Day_1::draw(GameState *gs, sf::RenderWindow &win)
{
	thought->draw(win);

	win.display();
}