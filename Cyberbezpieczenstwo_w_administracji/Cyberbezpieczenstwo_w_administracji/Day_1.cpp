#include "Day_1.h"
#include "GameState.h"

Day_1::Day_1()
{
	showButtons = false;
	init = false;
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
	change_lines = false;
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
	if(showButtons)
	{
		gs->choice1->setPosition(gs->officeLady->chat.getPosition().x ,gs->officeLady->chat.getPosition().y + gs->officeLady->chat.getGlobalBounds().height);
		gs->choice2->setPosition(gs->choice1->background.getPosition().x + gs->choice1->background.getGlobalBounds().width ,gs->choice1->background.getPosition().y );
	}
	else
	{
		gs->choice1->setPosition(0,-300);
		gs->choice2->setPosition(0,-300);
	}


	if (!init)
	{
		gs->computer->update(win);

		gs->officeApplicant->text.setTextString(L"Petent: Czeœæ! Marek dziœ nie w pracy?");
		gs->officeApplicant->addToQueue(L"Ja: Jego stanowisko zosta³o zajête.");
		gs->officeApplicant->addToQueue(L"Petent: Szkoda, dobrze nam siê z nim pracowa³o…");
		gs->officeApplicant->addToQueue(L"Ja: Nie spe³nia³ wymogów bezpieczeñstwa. ");
		gs->officeApplicant->addToQueue(L"Petent: Wiesz co siê sta³o?");
		gs->officeApplicant->addToQueue(L"Ja: Nie mogê Ci tego powiedzieæ.");
		gs->officeApplicant->addToQueue(L"Petent: Có¿, witaj w naszym zespole. Masz, to dla Ciebie.");

		gs->choice1->setText(L"zapisz has³o");
		gs->choice2->setText(L"nie zapisuj");

		init = true;
	}

	if (gs->lost)
	{
		init = false;
		if (gm::Core::getClock().getElapsedTime().asMilliseconds() > gs->info_time)
		{
			state = 0;
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

				gs->computer->setFillColor(gs->computer->getPressColor());
				gs->coffee->setFillColor(gs->coffee->getPressColor());
				gs->bell->setFillColor(gs->bell->getPressColor());
				gs->bin->setFillColor(gs->bin->getPressColor());
				gs->no_stamp->setFillColor(gs->no_stamp->getPressColor());
				gs->yes_stamp->setFillColor(gs->yes_stamp->getPressColor());
				gs->phone->setFillColor(gs->phone->getPressColor());
				gs->mobile->setFillColor(gs->mobile->getPressColor());
			}
			else if (gs->computer->clicked(win) || gs->book->clicked(win) || gs->bell->clicked(win) || gs->bin->clicked(win) || gs->no_stamp->clicked(win) || gs->yes_stamp->clicked(win) ||
					gs->phone->clicked(win) || gs->mobile->clicked(win))
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

				gs->computer->setFillColor(gs->computer->getPressColor());
				gs->coffee->setFillColor(gs->coffee->getPressColor());
				gs->bell->setFillColor(gs->bell->getPressColor());
				gs->bin->setFillColor(gs->bin->getPressColor());
				gs->no_stamp->setFillColor(gs->no_stamp->getPressColor());
				gs->yes_stamp->setFillColor(gs->yes_stamp->getPressColor());
				gs->book->setFillColor(gs->book->getPressColor());
				gs->mobile->setFillColor(gs->mobile->getPressColor());
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

				gs->computer->setFillColor(gs->computer->getPressColor());
				gs->coffee->setFillColor(gs->coffee->getPressColor());
				gs->bell->setFillColor(gs->bell->getPressColor());
				gs->bin->setFillColor(gs->bin->getPressColor());
				gs->no_stamp->setFillColor(gs->no_stamp->getPressColor());
				gs->yes_stamp->setFillColor(gs->yes_stamp->getPressColor());
				gs->phone->setFillColor(gs->phone->getPressColor());
				gs->mobile->setFillColor(gs->mobile->getPressColor());
				gs->book->setFillColor(gs->book->getPressColor());
			}

			break;
		case 5://Finish thought

			thought->animate();
			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				finish_thought = true;
				state++;
			}

			break;
		case 6://Choose user

			thought->animate();
			if(!thought->appearing && !thought->disappearing)
				thought->setBubblePosition(0, -300);

			gs->computer->update(win);
			gs->openedcomputer->update(win);
			if (gs->openedcomputer->getState() == OpenPC::DESKTOP)
			{
				choose_user = true;
				state++;
			}

			break;
		case 7://Login

			log_in = true;
			gs->computer->close();
			gs->officeApplicant->show();
			state++;

			break;
		case 8://Finish dialog

			if (gs->officeApplicant->state >= 6)
			{
				gs->officeApplicant->hide();
				finish_dialog = true;
				state++;

				gs->mobile->call();
			}

			break;
		case 9://Click mobile

			gs->mobile->update(win);
			if (gs->mobile->pickedUp)
			{
				click_mobile = true;
				state++;
			}

			break;
		case 10://Put mobile

			gs->mobile->update(win);
			if (!gs->mobile->pickedUp)
			{
				put_mobile = true;
				state++;

				gs->computer->open();

				gs->computer->setFillColor(gs->computer->getPressColor());
				gs->coffee->setFillColor(gs->coffee->getPressColor());
				gs->bell->setFillColor(gs->bell->getPressColor());
				gs->bin->setFillColor(gs->bin->getPressColor());
				gs->no_stamp->setFillColor(gs->no_stamp->getPressColor());
				gs->yes_stamp->setFillColor(gs->yes_stamp->getPressColor());
				gs->phone->setFillColor(gs->phone->getPressColor());
				gs->mobile->setFillColor(gs->mobile->getPressColor());
				gs->book->setFillColor(gs->book->getPressColor());
			}

			break;
		case 11://Change_lines

			if (gs->openedcomputer->getState() == OpenPC::SET_PASSWORD)
			{
				change_lines = true;
				state++;
			}
			else if (gs->openedcomputer->getState() == OpenPC::LOGIN_WIFI)
			{
				gs->lost = true;
				gs->eyelids->close();
				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
				gs->gamelost_info = new sf::Text;
				gs->gamelost_info->setFont(*gm::Assets::getFont());
				gs->gamelost_info->setString(L"Po³¹czy³eœ siê z internetem nie\nzmieniwszy wczeœniej danych logowania!");
				gs->gamelost_info->setCharacterSize(48);
				sf::Vector2f info_pos;
				info_pos.x = SCREEN_WIDTH / 2 - (gs->gamelost_info->getLocalBounds().left + gs->gamelost_info->getLocalBounds().width) / 2;
				info_pos.y = SCREEN_HEIGHT / 2 - (gs->gamelost_info->getLocalBounds().top + gs->gamelost_info->getLocalBounds().height) / 2;
				gs->gamelost_info->setPosition(sf::Vector2f(info_pos));
			}

			break;
		case 12://Remember password

			gs->computer->open();
			thought->animate();
			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				if (thought->scale <= 0.0)
					thought->setBubblePosition(0, -300);
			}
			if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD && gs->data->password == "Admin")
			{
				gs->lost = true;
				gs->eyelids->close();
				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
				gs->gamelost_info = new sf::Text;
				gs->gamelost_info->setFont(*gm::Assets::getFont());
				gs->gamelost_info->setString(L"Nie zmieni³eœ has³a i ktoœ wkrad³ siê na konto!");
				gs->gamelost_info->setCharacterSize(48);
				sf::Vector2f info_pos;
				info_pos.x = SCREEN_WIDTH / 2 - (gs->gamelost_info->getLocalBounds().left + gs->gamelost_info->getLocalBounds().width) / 2;
				info_pos.y = SCREEN_HEIGHT / 2 - (gs->gamelost_info->getLocalBounds().top + gs->gamelost_info->getLocalBounds().height) / 2;
				gs->gamelost_info->setPosition(sf::Vector2f(info_pos));
			}
			else if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD && gs->data->login != gs->data->name)
			{
				gs->openedcomputer->setState(OpenPC::SET_PASSWORD);
				thought->changeText(L"Login powinien byæ taki sam jak moje imiê...");
				thought->setBubblePosition(200,100);
				thought->showBubble();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			}
			else if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD)
			{
				gs->computer->close();
			}
			if(!gs->computer->isOpened())
			{
				gs->officeLady->show();
				remember_password = true;
				state++;
			}


			break;
		case 13://Write down password
			if(gs->officeLady->ready)
				showButtons = true;

			if(gs->choice1->clicked(gm::Core::getWindow()))
			{
				showButtons = false;
				gs->officeLady->hide();
				
				gs->lost = true;
				gs->eyelids->close();
				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
				gs->gamelost_info = new sf::Text;
				gs->gamelost_info->setFont(*gm::Assets::getFont());
				gs->gamelost_info->setString(L"Firma sprz¹taj¹ca Ministerstwo znalaz³a twoje has³o do systemu!");
				gs->gamelost_info->setCharacterSize(48);
				sf::Vector2f info_pos;
				info_pos.x = SCREEN_WIDTH / 2 - (gs->gamelost_info->getLocalBounds().left + gs->gamelost_info->getLocalBounds().width) / 2;
				info_pos.y = SCREEN_HEIGHT / 2 - (gs->gamelost_info->getLocalBounds().top + gs->gamelost_info->getLocalBounds().height) / 2;
				gs->gamelost_info->setPosition(sf::Vector2f(info_pos));
			}
			else if(gs->choice2->clicked(gm::Core::getWindow()))
			{
				showButtons = false;
				gs->officeLady->hide();
				write_down_password = true;
				state++;
				
				gs->openedcomputer->setState(OpenPC::DESKTOP);
				gs->computer->open();
			}

			break;
		case 14://Login wifi

			thought->animate();
			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				if (thought->scale <= 0.0)
					thought->setBubblePosition(0, -300);
			}
			if (gs->openedcomputer->getState() == OpenPC::SET_PASSWORD || !gs->computer->isOpened())
			{
				gs->openedcomputer->setState(OpenPC::DESKTOP);
				gs->computer->open();
				thought->changeText(L"Czas pod³¹czyæ siê do sieci...");
				thought->setBubblePosition(200, 100);
				thought->showBubble();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			}
			else if (gs->openedcomputer->getState() == OpenPC::LOGIN_WIFI)
			{
				login_wifi = true;
				state++;
			}

			break;
		case 15://Choose wifi

			//....
			gs->nextDay = true;

			break;
		case 16://Click email



			break;
		case 17://Refuse email



			break;
		default:
			break;
		}
	}
}

void Day_1::draw(GameState *gs, sf::RenderWindow &win)
{
	thought->draw(win);
	gs->officeApplicant->draw(win);

	win.display();
}