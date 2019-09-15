#include "Day_3.h"
#include "GameState.h"

Day_3::Day_3()
{
	showButtons = false;
	init = false;
	state = 0;
	
	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->changeText(L"W ko�cu usun�li konta starych u�ytkownik�w...");
	thought->setBubblePosition(0, -300);

	if (gm::Assets::getTexture("boss") == nullptr)
	{
		gm::Assets::LoadTexture("boss", TEXTURE_BELL);

		if (gm::Assets::getTexture("boss") == nullptr)
			error_win_close();
	}
	boss = new OfficeApplicant(gm::Assets::getTexture("boss"));

	boss->text.setTextString(L"Chyba nie chcecie podzieli� losu Anieli. Dokumenty w wersji papierowej to pie�� przesz�o�ci.");
	boss->addToQueue(L"Skoro nie potraficie ich upilnowa� to zeskanuj to i prze�lij do e-repozytorium.");
	boss->addToQueue(L"Po wszystkim teczki wracaj� do archiwum w piwnicy tam b�d� bezpieczne.");
	boss->addToQueue(L"By�bym zapomnia�. Oto twoje urz�dzenie wielofunkcyjne.");
	boss->addToQueue(L"Drukarka, Skaner i Xero w jednym. Jest nawet port USB. Nowiutka maszyna za pieni�dze z Unii.");
	boss->addToQueue(L"Sam bym chcia� tak� w gabinecie. Daj z siebie wszystko, chcemy chyba wygra� ten konkurs?");
	boss->addToQueue("EOT");
	boss->move(0, offset);
}

Day_3::~Day_3()
{
	delete thought;
	thought = nullptr;
	delete boss;
	boss = nullptr;
}

void Day_3::update(GameState *gs, sf::RenderWindow &win)
{
	thought->animate();
	boss->animate();

	if (showButtons)
	{
		if (state == 10)//Put mobile
		{
			gs->choice1->setPosition(MOBILE_POS_X - 300, MOBILE_POS_Y + 115);
			gs->choice2->setPosition(MOBILE_POS_X - 150, MOBILE_POS_Y + 115);
		}
		else if (state == 16)//Refuse wifi
		{
			if (gs->computer->isOpened())
			{
				gs->choice1->setPosition(MOBILE_POS_X - 300, MOBILE_POS_Y - 80);
				gs->choice2->setPosition(MOBILE_POS_X - 150, MOBILE_POS_Y - 80);
			}
			else
			{
				gs->choice1->setPosition(-300, 0);
				gs->choice2->setPosition(-300, 0);
			}
		}
		else
		{
			gs->choice1->setPosition(gs->officeLady->chat.getPosition().x, gs->officeLady->chat.getPosition().y + gs->officeLady->chat.getGlobalBounds().height);
			gs->choice2->setPosition(gs->choice1->background.getPosition().x + gs->choice1->background.getGlobalBounds().width, gs->choice1->background.getPosition().y);
		}
	}
	else
	{
		gs->choice1->setPosition(0, -300);
		gs->choice2->setPosition(0, -300);
	}

	if (!init)
	{
		gs->computer->update(win);

		gs->officeApplicant->text.setTextString(L"Petent: Cze��! Marek dzi� nie w pracy?");
		gs->officeApplicant->addToQueue(L"Ja: Jego stanowisko zosta�o zaj�te.");
		gs->officeApplicant->addToQueue(L"Petent: Szkoda, dobrze nam si� z nim pracowa�o�");
		gs->officeApplicant->addToQueue(L"Ja: Nie spe�nia� wymog�w bezpiecze�stwa. ");
		gs->officeApplicant->addToQueue(L"Petent: Wiesz co si� sta�o?");
		gs->officeApplicant->addToQueue(L"Ja: Nie mog� Ci tego powiedzie�.");
		gs->officeApplicant->addToQueue(L"Petent: C�, witaj w naszym zespole. Masz, to dla Ciebie.");
		gs->officeApplicant->addToQueue(L"EOT");//Dodatkowa linijka potrzebna

		gs->openedbook->setInfoL(L"1. Zabezpiecz dane logowania");
		gs->openedbook->setInfoR("");		

		gs->choice1->setText(L"zapisz has�o");
		gs->choice2->setText(L"nie zapisuj");

		init = true;
	}

	if (gs->lost)
	{
		init = false;
		if (gm::Core::getClock().getElapsedTime().asMilliseconds() > gs->info_time)
		{
			state = 0;
			gs->officeLady->hide();
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
				gs->gamelost_info->setString(L"Zasn��e� w pracy!\nPami�taj o kawie!");
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

				thought->setBubblePosition(300, 400);
				thought->showBubble();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			}

			break;
		case 3://Finish thought

			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				finish_thought = true;
				state++;

				gs->officeLady->show();
			}

			break;
		case 4://Finish dialog

			if (!thought->appearing && !thought->disappearing)
				thought->setBubblePosition(0, -300);


			if (gs->officeLady->state >= 3)
			{
				gs->officeLady->hide();
				finish_dialog = true;
				state++;

				boss->show();
			}

			break;
		case 5://Finish boss dialog

			if (boss->state >= 6)
			{
				boss->hide();
				finish_boss_dialog = true;
				state++;

				gs->openedcomputer->communique->setTextString(L"AWARIA FILTR�W EMAIL. ZALECANA OSTRO�NO��");
				gs->openedcomputer->show_communique = true;
				gs->computer->open();
			}

			break;
		case 6://Uncover xero

			if (!gs->computer->isOpened())
			{
				//xero->update();
			}


			break;
		case 7://Papers_on_desk



			break;
		case 8://Email warning



			break;
		case 9://Test scan



			break;
		case 10://Test scan2



			break;
		case 11://Test scan3



			break;
		case 12://Scan papers



			break;
		case 13://Finished scan



			break;
		case 14://Finish communique



			break;
		case 15://Broken scanner



			break;
		case 16://Fix scanner



			break;
		case 17://Finish thought 2



			break;
		case 18://Finish boss dialog 2



			break;
		case 19://Things vanish



			break;
		case 20://Phone pickup



			break;
		case 21://Finish phone



			break;
		case 22://Finish IT dialog 



			break;
		case 23://Mobile pickup



			break;
		case 24://Aniela talking



			break;
		case 25://Passed time



			break;
		case 26://Finish boss dialog



			break;
		default:



			break;

		}
	}
	std::cout << "end\n";
}

void Day_3::draw(GameState *gs, sf::RenderWindow &win)
{
	thought->draw(win);
	boss->draw(win);

	win.display();
}