#include "Day_3.h"
#include "GameState.h"

Day_3::Day_3()
{
	showButtons = true;
	init = false;
	state = 0;

	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->changeText(L"W koñcu usunêli konta starych u¿ytkowników...");
	thought->setBubblePosition(0, -300);

	ringIT = new textBubble(gm::Assets::getTexture("chat bubble"), 0.5);
	ringIT->setBubblePosition(0, -300);

	if (gm::Assets::getSound("beep") == nullptr)
	{
		gm::Assets::LoadSound("beep", SOUND_BEEP);

		if (gm::Assets::getSound("beep") == nullptr)
			error_win_close();
		else
			beep.setBuffer(*gm::Assets::getSound("beep"));
	}

	if (gm::Assets::getSound("boom") == nullptr)
	{
		gm::Assets::LoadSound("boom", SOUND_BOOM);

		if (gm::Assets::getSound("boom") == nullptr)
			error_win_close();
	}

	if (gm::Assets::getTexture("pc explosion") == nullptr)
	{
		gm::Assets::LoadTexture("pc explosion", PC_SCREEN_EXPLOSION);

		if (gm::Assets::getTexture("pc explosion") == nullptr)
			error_win_close();
	}

	if (gm::Assets::getTexture("pc broken") == nullptr)
	{
		gm::Assets::LoadTexture("pc broken", PC_SCREEN_CRACKED);

		if (gm::Assets::getTexture("pc broken") == nullptr)
			error_win_close();
	}

	if (gm::Assets::getTexture("lighting") == nullptr)
	{
		gm::Assets::LoadTexture("lighting", TEXTURE_LIGHTING);

		if (gm::Assets::getTexture("lighting") == nullptr)
			error_win_close();
	}
	lighting = new sf::Sprite(*gm::Assets::getTexture("lighting"));
	lighting->setPosition(-300, 0);


	if (gm::Assets::getTexture("boss") == nullptr)
	{
		gm::Assets::LoadTexture("boss", BOSS_TEXTURE);

		if (gm::Assets::getTexture("boss") == nullptr)
			error_win_close();
	}
	boss = new OfficeApplicant(gm::Assets::getTexture("boss"));

	if (gm::Assets::getTexture("ITguy") == nullptr)
	{
		gm::Assets::LoadTexture("ITguy", IT_GUY_TEXTURE);

		if (gm::Assets::getTexture("ITguy") == nullptr)
			error_win_close();
	}
	ITguy = new OfficeApplicant(gm::Assets::getTexture("ITguy"));

	if (gm::Assets::getTexture("peach") == nullptr)
	{
		gm::Assets::LoadTexture("peach", TEXTURE_PEACH);

		if (gm::Assets::getTexture("peach") == nullptr)
			error_win_close();
	}
	peach = new sf::Sprite[2];

	boss->text.setTextString(L"Chyba nie chcecie podzieliæ losu Anieli. Dokumenty w wersji papierowej to pieœñ przesz³oœci.");
	boss->addToQueue(L"Skoro nie potraficie ich upilnowaæ to zeskanuj to i przeœlij do e-repozytorium.");
	boss->addToQueue(L"Po wszystkim teczki wracaj¹ do archiwum w piwnicy tam bêd¹ bezpieczne.");
	boss->addToQueue(L"By³bym zapomnia³. Oto twoje urz¹dzenie wielofunkcyjne.");
	boss->addToQueue(L"Drukarka, Skaner i Xero w jednym. Jest nawet port USB. Nowiutka maszyna za pieni¹dze z Unii.");
	boss->addToQueue(L"Sam bym chcia³ tak¹ w gabinecie. Daj z siebie wszystko, chcemy chyba wygraæ ten konkurs?");
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
	ringIT->animate();
	boss->animate();
	ITguy->animate();
	gs->mariolka->animate();

	gs->mobile->pickedUp = false;

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
			gs->mariolka->hide();
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
				gs->gameover(L"Zasn¹³eœ w pracy! Pamiêtaj o kawie!");
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

				gs->mariolka->show();
				gs->playerIco.show();
			}

			break;
		case 4://Finish dialog

			if (!thought->appearing && !thought->disappearing)
				thought->setBubblePosition(0, -300);

			if (gs->mariolka->state > 0)
				gs->playerIco.hide();
			if (gs->mariolka->state >= 3)
			{
				gs->mariolka->hide();
				state++;

				boss->show();
			}

			break;
		case 5://Finish boss dialog
			
			if (boss->state == 1)
			{
				gs->papers->setPosition(PAPERS_POS);
			}
			else if (boss->state == 4)
			{
				gs->present->setPosition(XERO_POS_X, XERO_POS_Y);
			}
			else if (boss->state >= 6)
			{
				boss->hide();
				
				if (boss->hidden)
				{
					state++;

					gs->openedcomputer->communique->setTextString(L"AWARIA FILTRÓW EMAIL. ZALECANA OSTRO¯NOŒÆ!");
					gs->openedcomputer->show_communique = true;
					gs->computer->open();
				}
			}

			break;
		case 6://Warning

			if (gs->computer->isOpened())
			{
				if (gs->choice1->clicked(win))
				{
					gs->openedcomputer->show_communique = false;
					gs->computer->close();
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
				gs->choice1->setText(L"Skan próbny");
				gs->choice2->setText(L"Skan dokumentów");

				state++;
			}

			break;
		case 9://Test scan

			if (gs->choice1->clicked(win))
			{
				gs->choice1->setText(L"Ponowny skan próbny");
				gs->choice2->setText(L"Skan dokumentów");

				gs->xero->scanning.play();
				peach[0].setPosition(XERO_POS_X + XERO_WIDTH/2, XERO_POS_Y);
				scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 30000;
				gs->xero->putIn();

				state++;
			}
			else if (gs->choice2->clicked(win))
			{
				gs->xero->putIn();
				minigame.turned_on = true;
				state = 12;
			}

			break;
		case 10://Test scan2

			if (gm::Core::getClock().getElapsedTime().asMilliseconds() < scan_time)
			{
				if (peach[0].getPosition().y < 465)
				{
					peach[0].move(0, 10);
				}
				else
				{
					scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds();
					gs->xero->takeOut();
				}
			}
			else
			{
				if (gs->choice1->clicked(win))
				{
					gs->nagana(L"Nie marnuj papieru.Widzimy siê w moim gabinecie.B¹dŸ sam.WeŸ wydruki.");

					gs->xero->scanning.play();
					peach[1].setPosition(XERO_POS_X + XERO_WIDTH / 2 + 15, XERO_POS_Y);
					scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 30000;
					gs->xero->putIn();

					state++;
				}
				else if (gs->choice2->clicked(win))
				{
					gs->xero->putIn();
					minigame.turned_on = true;
					state = 12;
				}
			}

			break;
		case 11://Test scan3

			if (gm::Core::getClock().getElapsedTime().asMilliseconds() < scan_time)
			{
				if (peach[1].getPosition().y < 475)
				{
					peach[1].move(0, 10);
				}
				else
				{
					scan_time = gm::Core::getClock().getElapsedTime().asMilliseconds();
					gs->xero->takeOut();
				}
			}
			else
			{
				if (gs->choice1->clicked(win))
				{
					gs->gameover(L"Ksero siê popsu³o!");
				}
				else if (gs->choice2->clicked(win))
				{
					gs->xero->putIn();
					minigame.turned_on = true;
					state = 12;
				}
			}

			break;
		case 12://Scan papers

			gs->papers->setTexture(*gm::Assets::getTexture("PAPERS_4"));
			if (minigame.turned_on)
			{
				if (gs->xero->scanning.getStatus() == sf::Sound::Stopped)
				{
					gs->xero->scanning.play();
				}
				minigame.update(win);
			}
			else
			{
				gs->choice1->setText(L"OK");
				gs->openedcomputer->communique->setTextString(L"FILTRY ZNÓW DZIA£AJ¥!");
				gs->openedcomputer->show_communique = true;
				gs->computer->open();
				gs->xero->takeOut();
				gs->papers->setTexture(*gm::Assets::getTexture("PAPERS_3"));

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
					thought->text.setTextString(L"Zaciêcie papieru. POMOCY!!!");
					gs->xero->setTexture(gm::Assets::getTexture("XEROBROKEN"));

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
				gs->xero->putIn();
				gs->xero->setTexture(gm::Assets::getTexture("XERO"));

				state++;
			}

			break;
		case 15://Fix scanner

			if (!thought->appearing && !thought->disappearing)
			{
				thought->setBubblePosition(-300, 0);
			}
			if(scan_time < gm::Core::getClock().getElapsedTime().asMilliseconds() + 6000)
				gs->papers->setTexture(*gm::Assets::getTexture("PAPERS_2"));
			else if (scan_time < gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000)
				gs->papers->setTexture(*gm::Assets::getTexture("PAPERS_1"));
			if (scan_time > gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				if (gs->xero->scanning.getStatus() == sf::Sound::Stopped)
				{
					gs->xero->scanning.play();
				}
			}
			else
			{
				thought->showBubble();
				thought->setBubblePosition(250, 500);
				thought->text.setTextString(L"Ufff… tym razem oby³o siê bez zniszczenia dokumentów");
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
				gs->xero->takeOut();
				gs->papers->setPosition(-300, 0);

				state++;
			}

			break;
		case 16://Fix scanner

			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();

				while (!boss->text_queue.empty())
					boss->text_queue.pop();

				boss->text.setTextString(L"Widzê, ¿e skanowanie posz³o ci bardzo dobrze. Sprawdzi³em, ¿e skany s¹ ju¿ w cyfrowym repozytorium.");
				boss->addToQueue(L"Akta do archiwum zabierze Mariola. Ty zajmij siê zrobieniem kopii danych… emm jakiejœ zapaœniczej czy coœ.");
				boss->addToQueue(L"Najlepiej zadzwoñ do IT. Aaa i uwa¿aj w drodzê do domu dziœ zapowiadali burzê.");
				boss->addToQueue("EOT");
				boss->state = 0;
				boss->show();

				state++;
			}

			break;
		case 17://Finish thought 2

			if (!thought->appearing && !thought->disappearing)
			{
				thought->setBubblePosition(-300, 0);
			}
			if (boss->state >= 3)
			{
				boss->hide();
				gs->mariolka->show();
				gs->papers->setTexture(*gm::Assets::getTexture("PAPERS_5"));

				state++;
			}

			break;
		case 18://Finish boss dialog 2

			if (gs->mariolka->getPosition().x < 850)
			{
				gs->papers->setPosition(750, 350);
				gs->mariolka->hide();
				ringIT->showBubble();
				gs->mobile->call();
				gs->phone->setFillColor(sf::Color::White);

				state++;
			}

			break;
		case 19://Things vanish

			gs->mobile->update(win);
			if (gs->papers->getPosition().x < gs->mariolka->getPosition().x)
				gs->papers->move(10, 0);
			if (gs->phone->aimed(win))
			{
				ringIT->setBubblePosition(5, 470);
				ringIT->text.setTextString(L"Zadzwoñ do IT");

				if (gs->phone->clicked(win))
				{
					ringIT->setBubblePosition(-300, 0);
					ringIT->closeBubble();

					
					while (!gs->phone->text_queue.empty())
						gs->phone->text_queue.pop();

					gs->phone->text.setTextString(L"Tu dzia³ IT s³ucham? \n *Mariusz ile mo¿na czekaæ, koñcz swoj¹ turê! Gramy czy nie?!*");
					gs->phone->addToQueue(L"S³uchaj a mo¿e zrobimy to jutro? Dziœ jesteœmy bardzo zajêci… NO POCZEKAJ NO ZDOBYWAM ZAMEK!!!");
					gs->phone->addToQueue(L"Nic, nic. Bêdziemy za 5 minut.");

					while (!gs->playerIco.text_queue.empty())
						gs->playerIco.text_queue.pop();
					gs->playerIco.text.setTextString(L"Halo? IT? Pomo¿ecie mi skonfigurowaæ kopiê zapasow¹?");

					gs->phone->pickedUp = true;
					gs->playerIco.show();

					state++;
				}
			}
			else if (gs->mobile->aimed(win))
			{
				ringIT->setBubblePosition(585, 475);
				ringIT->text.setTextString(L"Dzwoni Aniela Ministerstwo");

				if (gs->mobile->pickedUp)
				{
					ringIT->setBubblePosition(-300, 0);
					ringIT->closeBubble();
					gs->mobile->pickedUp = false;
					state = 23;

					gs->naganiony = true;
					gs->nagana_info = new sf::Text;
					gs->nagana_info->setOutlineThickness(5);
					gs->nagana_info->setOutlineColor(sf::Color::Black);
					gs->nagana_info->setFont(*gm::Assets::getFont());
					gs->nagana_info->setString(L"Pocieszanie Anieli...");
					gs->nagana_info->setFillColor(sf::Color::White);
					gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
					sf::Vector2f info_pos;
					info_pos.x = SCREEN_WIDTH / 2 - (gs->nagana_info->getLocalBounds().left + gs->nagana_info->getLocalBounds().width) / 2;
					info_pos.y = SCREEN_HEIGHT / 2 - (gs->nagana_info->getLocalBounds().top + gs->nagana_info->getLocalBounds().height) / 2;
					gs->nagana_info->setPosition(sf::Vector2f(info_pos));
				}
			}
			else
				ringIT->setBubblePosition(-300, 0);

			break;
		case 20://Phone pickup

			if (gs->papers->getPosition().x < gs->mariolka->getPosition().x)
				gs->papers->move(10, 0);

			gs->phone->update(win);
			if (!gs->phone->pickedUp)
			{
				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 5000;
				gs->playerIco.hide();

				state++;
			}
			else
			{
				if (gs->phone->text_queue.size() == 2)
				{
					gs->playerIco.text.setTextString(L"Halo? IT? Pomo¿ecie mi skonfigurowaæ kopiê zapasow¹?");
				}
				else if (gs->phone->text_queue.size() == 1)
				{
					gs->playerIco.text.setTextString(L"...");
				}
				else if (gs->phone->text_queue.size() == 0)
				{
					gs->playerIco.text.setTextString(L"S£UCHAM?");
				}
			}

			break;
		case 21://Finish phone

			if (gs->info_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				while (!ITguy->text_queue.empty())
					ITguy->text_queue.pop();

				ITguy->text.setTextString(L"Kopia zapasowa to bardzo wa¿ny element cyberbezpieczeñstwa Ministerstwa.");
				ITguy->addToQueue(L"Pamiêtaj, aby wykonywaæ j¹ przynajmniej raz w tygodniu. Dziêki temu nasze szanse na wygran¹ w konkursie rosn¹.");
				ITguy->addToQueue("EOT");
				ITguy->show();

				state++;
			}

			break;
		case 22://Finish IT dialog 

			if (ITguy->state >= 2)
			{
				ITguy->hide();

				while (!boss->text_queue.empty())
					boss->text_queue.pop();

				boss->state = 0;

				boss->text.setTextString(L"Dopóki nowa kole¿anka nie przejdzie wymaganych szkoleñ bêdziesz odpowiada³ równie¿ za obs³ugê petentów.");
				boss->addToQueue(L"Zaczniesz od jutra. Zobaczymy jak sobie poradzisz. Kto wie mo¿e j¹ zast¹pisz. Na dziœ to wszystko, idŸ do domu.");
				boss->addToQueue("EOT");
				
				boss->show();

				state = 26;
			}

			break;
		case 23://Mobile pickup

			if (gs->info_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				gs->computer->blackScreen.setTexture(*gm::Assets::getTexture("pc explosion"));
				lighting->setPosition(100, 0);
				state++;

				beep.setBuffer(*gm::Assets::getSound("boom"));
				beep.play();
				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 100;
			}
			else
			{
				gs->watch->setHour(gs->watch->getHours(), gs->watch->getMinutes() + 1);
			}

			break;
		case 24://Aniela talking

			if (gs->info_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				lighting->setPosition(-300, 0);
				gs->computer->blackScreen.setTexture(*gm::Assets::getTexture("pc broken"));
				state++;

				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 3000;
			}

			break;
		case 25://Passed time

			if (gs->info_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				gs->gameover(L"Nie wykona³eœ kopii bezpieczeñstwa. Burza spali³a dysk twardy w twoim komputerze, przez co znaczn¹ czêœæ zasobów Ministerstwa bezpowrotnie utracono."
							 L"Zostajesz zwolniony dyscyplinarnie w trybie natychmiastowym.");
			}

			break;
		case 26://Finish boss dialog

			if (boss->state >= 2)
			{
				boss->hide();
				state++;
			}

			break;
		case 27://End

			gs->exit->setFillColor(sf::Color::White);
			if (gs->exit->clicked(win))
			{
				gs->dayover(L"-obs³uga kserokopiarki\n"
					L"-wykonywanie kopii dokumentów\n"
					L"-odpieranie ataków phishingowych\n"
					L"-skupianie siê na swojej pracy\n");
				gs->nextDay = true;
			}

			break;
		default:



			break;

		}
	}
}

void Day_3::draw(GameState *gs, sf::RenderWindow &win)
{
	win.draw(*lighting);
	thought->draw(win);
	boss->draw(win);
	ITguy->draw(win);
	gs->mariolka->draw(win);
	for (int i = 0; i < 2; i++)
	{
		win.draw(peach[i]);
	}
	ringIT->draw(win);

	if(minigame.turned_on)
		minigame.draw(win);

	win.display();
}