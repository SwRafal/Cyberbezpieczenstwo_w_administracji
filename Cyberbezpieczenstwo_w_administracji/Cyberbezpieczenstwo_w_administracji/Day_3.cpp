#include "Day_3.h"
#include "GameState.h"

Day_3::Day_3()
{
	showButtons = true;
	init = false;
	state = 0;
	
	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->changeText(L"W ko�cu usun�li konta starych u�ytkownik�w...");
	thought->setBubblePosition(0, -300);

	if (gm::Assets::getSound("beep") == nullptr)
	{
		gm::Assets::LoadSound("beep", SOUND_BEEP);

		if (gm::Assets::getSound("beep") == nullptr)
			error_win_close();
		else
			beep.setBuffer(*gm::Assets::getSound("beep"));
	}

	if (gm::Assets::getTexture("boss") == nullptr)
	{
		gm::Assets::LoadTexture("boss", BOSS_TEXTURE);

		if (gm::Assets::getTexture("boss") == nullptr)
			error_win_close();
	}
	boss = new OfficeApplicant(gm::Assets::getTexture("boss"));

	if (gm::Assets::getTexture("peach") == nullptr)
	{
		gm::Assets::LoadTexture("peach", TEXTURE_PEACH);

		if (gm::Assets::getTexture("peach") == nullptr)
			error_win_close();
	}
	peach = new sf::Sprite[2];

	boss->text.setTextString(L"Chyba nie chcecie podzieli� losu Anieli. Dokumenty w wersji papierowej to pie�� przesz�o�ci.");
	boss->addToQueue(L"Skoro nie potraficie ich upilnowa� to zeskanuj to i prze�lij do e-repozytorium.");
	boss->addToQueue(L"Po wszystkim teczki wracaj� do archiwum w piwnicy tam b�d� bezpieczne.");
	boss->addToQueue(L"By�bym zapomnia�. Oto twoje urz�dzenie wielofunkcyjne.");
	boss->addToQueue(L"Drukarka, Skaner i Xero w jednym. Jest nawet port USB. Nowiutka maszyna za pieni�dze z Unii.");
	boss->addToQueue(L"Sam bym chcia� tak� w gabinecie. Daj z siebie wszystko, chcemy chyba wygra� ten konkurs?");
	boss->addToQueue("EOT");
	boss->move(0, offset);

	for (int i = 0; i < 2; i++)
	{
		peach[i].setTexture(*gm::Assets::getTexture("peach"));
		peach[i].setRotation(10);
		peach[i].setPosition(-300, 0);
	}
}

Day_3::~Day_3()
{
	delete thought;
	thought = nullptr;
	delete boss;
	boss = nullptr;
	delete[] peach;
	peach = nullptr;
}

void Day_3::update(GameState *gs, sf::RenderWindow &win)
{
	thought->animate();
	boss->animate();

	if (gs->info_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
	{
		gs->naganiony = false;
	}

	if (showButtons)
	{
		if ((state == 6 || state == 13) && gs->computer->isOpened())//Put mobile
		{
			gs->choice1->setPosition(SCREEN_WIDTH/2 - 110, SCREEN_HEIGHT/2 + 80);
		}
		else if (state >= 9 && state <= 11)
		{
			gs->choice1->setPosition(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 80);
			gs->choice2->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80);
		}
		else
		{
			gs->choice1->setPosition(0, -300);
			gs->choice2->setPosition(0, -300);
		}
	}

	if (!init)
	{
		gs->computer->update(win);

		gs->xero->setPosition(sf::Vector2f(-300, 0));
		gs->present->setPosition(sf::Vector2f(-300, 0));

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

		gs->choice1->setText(L"OK");
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
				gs->gameover(L"Zasn��e� w pracy! Pami�taj o kawie!");
			}

			break;
		case 1://Open book

			if (gs->book->clicked(win))
			{
				gs->book->open();
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
				state++;

				boss->show();
			}

			break;
		case 5://Finish boss dialog
			if (boss->state >= 4)
			{
				gs->present->setPosition(XERO_POS_X, XERO_POS_Y);
			}
			if (boss->state >= 1)
			{
				gs->papers->setPosition(PAPERS_POS);
			}
			if (boss->state >= 6)
			{
				boss->hide();
				state++;

				gs->openedcomputer->communique->setTextString(L"AWARIA FILTR�W EMAIL. ZALECANA OSTRO�NO��");
				gs->openedcomputer->show_communique = true;
				gs->computer->open();
			}

			break;
		case 6://Warning

			if (gs->computer->isOpened())
			{
				if (gs->choice1->clicked(win))
				{
					gs->openedcomputer->show_communique = false;
					state++;
				}
			}

			break;
		case 7://Uncover xero

			if (!gs->computer->isOpened())
			{
				if (gs->present->clicked(win))
				{
					gs->present->setPosition(-300, 0);
					gs->xero->setPosition(XERO_POS_X, XERO_POS_Y);
					state++;
				}
			}

			break;
		case 8://Click Xero

			if (gs->xero->clicked(win))
			{
				gs->choice1->setText(L"Skan pr�bny");
				gs->choice2->setText(L"Skan dokument�w");

				state++;
			}

			break;
		case 9://Test scan

			if (gs->choice1->clicked(win))
			{
				gs->choice1->setText(L"Ponowny skan pr�bny");
				gs->choice2->setText(L"Skan dokument�w");

				gs->xero->scanning.play();
				peach[0].setPosition(XERO_POS_X + XERO_WIDTH/2, XERO_POS_Y);
				scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;

				state++;
			}
			else if (gs->choice2->clicked(win))
			{
				scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 30000;
				state = 12;
			}

			break;
		case 10://Test scan2

			if (gm::Core::getClock().getElapsedTime().asMilliseconds() < scan_time)
			{
				if (peach[0].getPosition().y < 455)
				{
					peach[0].move(0, 10);
				}
				else
					scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds();
			}
			else
			{
				if (gs->choice1->clicked(win))
				{
					gs->nagana(L"Nie marnuj papieru.Widzimy si� w moim gabinecie.B�d� sam.We� wydruki.");

					gs->xero->scanning.play();
					peach[1].setPosition(XERO_POS_X + XERO_WIDTH / 2 + 15, XERO_POS_Y);
					scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;

					state++;
				}
				else if (gs->choice2->clicked(win))
				{
					scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 30000;
					state = 12;
				}
			}

			break;
		case 11://Test scan3

			if (gm::Core::getClock().getElapsedTime().asMilliseconds() < scan_time)
			{
				if (peach[1].getPosition().y < 465)
				{
					peach[1].move(0, 10);
				}
				else
					scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds();
			}
			else
			{
				if (gs->choice1->clicked(win))
				{
					gs->gameover(L"Ksero si� popsu�o!");
				}
				else if (gs->choice2->clicked(win))
				{
					scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 30000;
					state = 12;
				}
			}

			break;
		case 12://Scan papers

			if (scan_time > gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				if (gs->xero->scanning.getStatus() == sf::Sound::Stopped)
				{
					gs->xero->scanning.play();
					
				}
				gs->papers->move(0, 0.08);
			}
			else
			{
				gs->choice1->setText(L"OK");
				gs->openedcomputer->communique->setTextString(L"FILTRY ZN�W DZIA�AJ�!");
				gs->openedcomputer->show_communique = true;
				gs->computer->open();
				state++;
			}
				

			break;
		case 13://Finished scan

			if (gs->computer->isOpened())
			{
				if (gs->choice1->clicked(win))
				{
					gs->openedcomputer->show_communique = false;
					gs->computer->close();

					thought->showBubble();
					thought->setBubblePosition(900, 100);
					thought->text.setTextString(L"Zaci�cie papieru. POMOCY!!!");
					

					state++;
				}
			}

			break;
		case 14://Broken scanner

			if (beep.getStatus() == sf::Sound::Stopped)
			{
				beep.play();
			}
			if (gs->xero->clicked(win))
			{
				thought->closeBubble();

				scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 12000;

				state++;
			}

			break;
		case 15://Fix scanner

			if (!thought->appearing && !thought->disappearing)
			{
				thought->setBubblePosition(-300, 0);
			}

			if (scan_time > gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				if (gs->xero->scanning.getStatus() == sf::Sound::Stopped)
				{
					gs->xero->scanning.play();

				}
				gs->papers->move(0, 0.08);
			}
			else
			{
				thought->showBubble();
				thought->setBubblePosition(250, 500);
				thought->text.setTextString(L"Ufff� tym razem oby�o si� bez zniszczenia dokument�w");
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;

				state++;
			}

			break;
		case 16://Fix scanner

			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();

				while (!boss->text_queue.empty())
					boss->text_queue.pop();

				boss->text.setTextString(L"Widz�, �e skanowanie posz�o ci bardzo dobrze. Sprawdzi�em, �e skany s� ju� w cyfrowym repozytorium.");
				boss->addToQueue(L"Akta do archiwum zabierze Mariola. Ty zajmij si� zrobieniem kopii danych� emm jakiej� zapa�niczej czy co�.");
				boss->addToQueue(L"Najlepiej zadzwo� do IT. Aaa i uwa�aj w drodz� do domu dzi� zapowiadali burz�.");
				boss->addToQueue("EOT");
				boss->state = 0;
				boss->show();

				state++;
			}

			break;
		case 17://Finish thought 2

			if (!thought->appearing && !thought->disappearing)
			{
				thought->setBubblePosition(-300,0);
			}
			if (boss->state >= 3)
			{
				boss->hide();
				state++;
			}

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
}

void Day_3::draw(GameState *gs, sf::RenderWindow &win)
{
	thought->draw(win);
	boss->draw(win);
	for (int i = 0; i < 2; i++)
	{
		win.draw(peach[i]);
	}

	win.display();
}