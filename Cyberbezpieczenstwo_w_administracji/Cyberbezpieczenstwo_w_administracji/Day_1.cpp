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

	talked = false;
	talked2 = false;

	//Initialize
	ITguy = new OfficeApplicant(gm::Assets::getTexture("itGuy"));

}

Day_1::~Day_1()
{
	delete thought;
	thought = nullptr;
	delete ITguy;
	ITguy = nullptr;
}

void Day_1::update(GameState *gs, sf::RenderWindow &win)
{
	thought->animate();
	if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
	{
		thought->closeBubble();
		if (thought->scale <= 0.0)
			thought->setBubblePosition(0, -300);
	}

	if(showButtons)
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
				gs->choice1->setPosition(MOBILE_POS_X - 300, MOBILE_POS_Y - 110);
				gs->choice2->setPosition(MOBILE_POS_X - 150, MOBILE_POS_Y - 110);
			}
			else
			{
				gs->choice1->setPosition(-300, 0);
				gs->choice2->setPosition(-300, 0);
			}
		}
		else if (state == 20)
		{
			gs->choice1->setPosition(420, 500);
			gs->choice2->setPosition(620, 500);
		}
		else
		{
			gs->choice1->setPosition(gs->officeLady->chat.getPosition().x, gs->officeLady->chat.getPosition().y + gs->officeLady->chat.getGlobalBounds().height);
			gs->choice2->setPosition(gs->choice1->background.getPosition().x + gs->choice1->background.getGlobalBounds().width, gs->choice1->background.getPosition().y);
		}
	}
	else
	{
		gs->choice1->setPosition(0,-300);
		gs->choice2->setPosition(0,-300);
	}


	if (!init)
	{
		gs->computer->update(win);

		gs->officeApplicant->text.setTextString(L"Cze��! Marek dzi� nie w pracy?");
		//gs->officeApplicant->addToQueue(L"Ja: Jego stanowisko zosta�o zaj�te.");
		gs->officeApplicant->addToQueue(L"Szkoda, dobrze nam si� z nim pracowa�o�");
		//gs->officeApplicant->addToQueue(L"Ja: Nie spe�nia� wymog�w bezpiecze�stwa. ");
		gs->officeApplicant->addToQueue(L"Wiesz co si� sta�o?");
		//gs->officeApplicant->addToQueue(L"Ja: Nie mog� Ci tego powiedzie�.");
		gs->officeApplicant->addToQueue(L"C�, witaj w naszym zespole. Masz, to dla Ciebie.");
		gs->officeApplicant->addToQueue(L"EOT");//Dodatkowa linijka potrzebna

		gs->playerIco.text.setTextString(L"Jego stanowisko zosta�o zaj�te.");
		gs->playerIco.addToQueue(L"Nie spe�nia� wymog�w bezpiecze�stwa.");
		gs->playerIco.addToQueue(L"Nie mog� Ci tego powiedzie�.");
		
		ITguy->text.setTextString(L"Tym Ci� pod��czymy do sieci.");
		ITguy->addToQueue(L"EOT");//Dodatkowa linijka potrzebna

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
		ITguy->animate();

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

				gs->phone->call();
			}

			break;
		case 3://Click telephone

			gs->phone->update(win);
			if (gs->phone->pickedUp)
			{
				state++;
			}

			break;
		case 4://Finish telephone

			gs->phone->update(win);
			if (!gs->phone->pickedUp)
			{
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

			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				state++;
			}

			break;
		case 6://Choose user

			if (!thought->appearing && !thought->disappearing)
				thought->setBubblePosition(0, -300);

			gs->computer->update(win);
			gs->openedcomputer->update(win);
			if (gs->openedcomputer->getState() == OpenPC::DESKTOP)
			{
				state++;
			}

			break;
		case 7://Login

			gs->computer->close();
			gs->officeApplicant->show();
			state++;

			break;
		case 8://Finish dialog
			
			if (gs->officeApplicant->state == 1)
				gs->playerIco.show();
			else if (gs->officeApplicant->state == 2)
			{
				if (talked == false)
				{
					talked = true;
					gs->playerIco.nextLine();
				}
			}
			else if (gs->officeApplicant->state == 3)
			{
				if (talked2 == false)
				{
					talked2 = true;
					gs->playerIco.nextLine();
				}
				gs->sushi.setPosition(830, 400);
			}
			else if (gs->officeApplicant->state >= 4)
			{
				gs->playerIco.hide();
				gs->officeApplicant->hide();
				state++;

				gs->mobile->call();
				gs->sushi.setPosition(830, 400);
			}

			break;
		case 9://Click mobile

			gs->mobile->update(win);
			if (gs->sushi.getPosition().y < 500)
				gs->sushi.move(0, 2);
			if (gs->mobile->pickedUp)
			{
				showButtons = true;
				gs->choice1->setText(L"Wy�lij");
				gs->choice2->setText(L"Nie wysy�aj");

				state++;
			}

			break;
		case 10://Put mobile

			gs->mobile->update(win);
			if (showButtons)
			{
				if (gs->choice1->clicked(gm::Core::getWindow()))
				{
					thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
					gs->mobile->text.setTextString(L"WYS�ANO!\nKoszt wiadomo�ci to 450z�.");
					gs->data->sms_sent = true;
					showButtons = false;
				}
				else if (gs->choice2->clicked(gm::Core::getWindow()))
				{
					showButtons = false;
					gs->mobile->pickedUp = false;
				}
			}
			else if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				gs->mobile->pickedUp = false;
			}

			if (!gs->mobile->pickedUp)
			{

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
		case 11://Change_lines

			if (!gs->computer->isOpened())
				gs->computer->update(win);
			if (gs->openedcomputer->getState() == OpenPC::SET_PASSWORD)
			{
				state++;
			}
			else if (gs->openedcomputer->getState() == OpenPC::LOGIN_WIFI)
			{
				gs->gameover(L"Po��czy�e� si� z internetem, nie zmieniwszy wcze�niej danych logowania!");
			}

			break;
		case 12://Remember password

			gs->computer->open();
			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				if (thought->scale <= 0.0)
					thought->setBubblePosition(0, -300);
			}
			if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD && gs->data->password == "Admin")
			{
				gs->gameover(L"Nie zmieni�e� has�a i kto� wkrad� si� na konto!");
			}
			else if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD && gs->data->password == gs->openedcomputer->getLogin())
			{
				gs->gameover(L"Has�o by�o takie same jak login. Kto� wkrad� si� na konto!");
			}
			else if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD && gs->data->login != gs->data->name)
			{
				gs->openedcomputer->setState(OpenPC::SET_PASSWORD);
				thought->changeText(L"Login powinien by� taki sam jak moje imi�...");
				thought->setBubblePosition(200, 100);
				thought->showBubble();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			}
			else if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD && gs->data->password.getSize() < 6)
			{
				gs->openedcomputer->setState(OpenPC::SET_PASSWORD);
				thought->changeText(L"Has�o jest za kr�tkie...");
				thought->setBubblePosition(200, 100);
				thought->showBubble();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			}
			else if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD)
			{
				bool small_letter = false;
				bool big_letter = false;

				for (int i = 0; i < gs->data->password.getSize(); i++)
				{
					if (gs->data->password[i] >= 'A' && gs->data->password[i] <= 'Z')
						big_letter = true;
					else if (gs->data->password[i] >= 'a' && gs->data->password[i] <= 'z')
						small_letter = true;
				}

				if (small_letter && big_letter)
				{
					gs->data->login = gs->openedcomputer->getLogin();
					gs->data->password = gs->openedcomputer->getPassword();
					gs->computer->close();
				}
				else
				{
					gs->openedcomputer->setState(OpenPC::SET_PASSWORD);
					thought->changeText(L"Has�o jest za s�abe... Spr�buj wielkich liter.");
					thought->setBubblePosition(200, 100);
					thought->showBubble();
					thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
				}				
			}
			if (!gs->computer->isOpened())
			{
				gs->officeLady->show();
				gs->choice1->setText(L"Zapisz");
				gs->choice2->setText(L"Nie zapisuj");
				state++;
			}

			break;
		case 13://Write down password
			if (gs->officeLady->ready)
				showButtons = true;

			if (gs->choice1->clicked(gm::Core::getWindow()))
			{
				showButtons = false;
				gs->officeLady->hide();

				gs->gameover(L"Firma sprz�taj�ca Ministerstwo znalaz�a twoje has�o do systemu!");
			}
			else if (gs->choice2->clicked(gm::Core::getWindow()))
			{
				showButtons = false;
				gs->officeLady->hide();
				state++;

				gs->openedcomputer->setState(OpenPC::DESKTOP);
			}

			break;
		case 14://Login wifi

			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				if (thought->scale <= 0.0)
					thought->setBubblePosition(0, -300);
			}
			if (!gs->computer->isOpened())
				gs->computer->update(win);
			if (gs->openedcomputer->getState() == OpenPC::SET_PASSWORD)
			{
				gs->openedcomputer->setState(OpenPC::DESKTOP);
				thought->changeText(L"Czas pod��czy� si� do sieci...");
				thought->setBubblePosition(200, 100);
				thought->showBubble();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			}
			else if (gs->openedcomputer->getState() == OpenPC::LOGIN_WIFI)
			{
				state++;
			}

			break;
		case 15://Choose wifi

			if (gs->openedcomputer->show_communique)
			{
				showButtons = true;
				gs->choice1->setText(L"Pobierz");
				gs->choice2->setText(L"Anuluj");
				state++;
			}
			else
			{
				if (!gs->computer->isOpened())
					gs->computer->update(win);
				if (gs->openedcomputer->getState() == OpenPC::DESKTOP)
				{
					gs->openedcomputer->setState(OpenPC::LOGIN_WIFI);
					thought->changeText(L"Czas pod��czy� si� do sieci...");
					thought->setBubblePosition(200, 100);
					thought->showBubble();
					thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
				}
			}

			break;
		case 16://Refuse wifi

			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				if (thought->scale <= 0.0)
					thought->setBubblePosition(0, -300);
			}
			if (gs->naganiony)
			{
				gs->computer->close();
				if (gs->info_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
				{
					gs->naganiony = false;
					gs->openedcomputer->setState(OpenPC::DESKTOP);
					gs->openedcomputer->internet_works = true;
					state+=3;

					ITguy->show();
					gs->rj45.setPosition(830, 400);
				}
			}
			else
			{
				if (gs->choice1->clicked(gm::Core::getWindow()))
				{
					showButtons = false;
					gs->openedcomputer->show_communique = false;
					gs->naganiony = true;
					gs->data->nagany++;
					gs->nagana_info = new sf::Text;
					gs->nagana_info->setFont(*gm::Assets::getFont());
					gs->nagana_info->setString(L"Zainstalowa�e� certyfikat z niepewnego �r�d�a. Skontaktuj si� z dzia�em IT!");
					gs->nagana_info->setFillColor(sf::Color::Red);
					gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
					sf::Vector2f info_pos;
					info_pos.x = SCREEN_WIDTH / 2 - (gs->nagana_info->getLocalBounds().left + gs->nagana_info->getLocalBounds().width) / 2;
					info_pos.y = SCREEN_HEIGHT / 2 - (gs->nagana_info->getLocalBounds().top + gs->nagana_info->getLocalBounds().height) / 2;
					gs->nagana_info->setPosition(sf::Vector2f(info_pos));

				}
				else if (gs->choice2->clicked(gm::Core::getWindow()))
				{
					showButtons = false;
					gs->openedcomputer->show_communique = false;
					gs->openedcomputer->setState(OpenPC::DESKTOP);
					gs->computer->close();
					gs->openedcomputer->internet_works = true;
					state++;

					while (!gs->phone->text_queue.empty())
					{
						gs->phone->text_queue.pop();
					}
					while (!gs->playerIco.text_queue.empty())
					{
						gs->playerIco.text_queue.pop();
					}
					gs->playerIco.state = 0;
					gs->playerIco.text.setTextString(L"Cze�� tu " + gs->data->name + L"! Nie mog� po��czy� si� z sieci�, pomo�ecie?");
					gs->phone->addToQueue(L"Pomo�emy!!!");
					gs->phone->call();

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
			}

			break;
		case 17://PhoneIT

			if (gs->phone->pickedUp)
			{
				gs->playerIco.show();
				state++;
			}
			else
				gs->phone->update(win);

			break;
		case 18://Finish ITphone

			if (gs->phone->pickedUp)
				gs->phone->update(win);
			else
			{
				ITguy->show();
				gs->rj45.setPosition(830, 400);
				gs->playerIco.hide();
				state++;
			}

			break;
		case 19://RJ45
			
			if (gs->naganiony)
			{
				gs->rj45.setPosition(-300, 0);

				if (gs->info_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
				{
					gs->naganiony = false;
					state++;

					gs->computer->open();
					gs->openedcomputer->setState(OpenPC::MAIL);
					gs->openedcomputer->newMail(L"Passwordmanagers",L"dzia�IT@Mindswszelakich.pl", L"Szanowny urz�dniku!\nPami�taj, aby nigdy nie zapisywa� swoich hase� w miejscach, "
																									L"do kt�rych kto� nieupowa�niony mo�e mie� dost�p.\n"
																									L"W Ministerstwie u�ywamy specjalnego programu do zarz�dzania has�ami, pobierz go z za��cznika poni�ej i dok�adnie przeczytaj instrukcje.\n\n"
																									L"Za��cznik: Passmen.exe");
					showButtons = true;
					gs->choice1->setText(L"Pobierz");
					gs->choice2->setText(L"Odrzu�");
				}
			}
			else if (ITguy->state >= 1)
			{
				ITguy->hide();
				gs->naganiony = true;
				gs->nagana_info = new sf::Text;
				gs->nagana_info->setFont(*gm::Assets::getFont());
				gs->nagana_info->setString(L"Dost�p do sieci przyznany!");
				gs->nagana_info->setFillColor(sf::Color::Green);
				gs->nagana_info->setOutlineThickness(3);
				gs->nagana_info->setOutlineColor(sf::Color::Black);
				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
				sf::Vector2f info_pos;
				info_pos.x = SCREEN_WIDTH / 2 - (gs->nagana_info->getLocalBounds().left + gs->nagana_info->getLocalBounds().width) / 2;
				info_pos.y = SCREEN_HEIGHT / 2 - (gs->nagana_info->getLocalBounds().top + gs->nagana_info->getLocalBounds().height) / 2;
				gs->nagana_info->setPosition(sf::Vector2f(info_pos));					
			}
			else if(gs->rj45.getPosition().y < 500)
			{	
					gs->rj45.move(0, 2);
			}

			break;
		case 20://Click email

			gs->openedcomputer->setState(OpenPC::MAIL);
			if (gs->choice1->clicked(win))
				gs->gameover(L"Pobra�e� i zainstalowa�e� zawirusowany za��cznik z nieautoryzowanego �r�d�a. Twoje has�o do systemu zosta�o skradzione." 
							 L"W wyniku twoich dzia�a� dosz�o do wycieku danych Ministerstwa a jego wiarygodno�� zosta�a zrujnowana. Zostajesz zwolniony dyscyplinarnie w trybie natychmiastowym.");
			else if (gs->choice2->clicked(win))
			{
				while (!ITguy->text_queue.empty())
					ITguy->text_queue.pop();

				ITguy->text.setTextString(L"Pracownikom bez specjalnych uprawnie� nie wolno samodzielnie instalowa� �adnych program�w.");
				ITguy->addToQueue(L"Programy z niezaufanych �r�de� s� niebezpieczene.");
				ITguy->addToQueue(L"Dzia� IT zajmie si� instalacj� potrzebnego ci oprogramowania.");
				ITguy->addToQueue(L"Istotnie dobrze jest tworzy� i zapisywa� has�a w menad�erze hase�,");
				ITguy->addToQueue(L"wtedy s� one bezpieczne i musisz zapami�ta� tylko jedno has�o � do menad�era.");
				ITguy->addToQueue(L"Na dzi� dzi�kujemy mo�esz wraca� do domu.");
				ITguy->addToQueue(L"EOT");
				ITguy->state = 0;
				ITguy->show();

				gs->openedcomputer->setState(OpenPC::USERS);
				gs->computer->close();
				showButtons = false;

				state++;
			}

			break;
		case 21://Dialog

			if (ITguy->state >= 6)
			{
				ITguy->hide();
				if (ITguy->hidden)
				{
					gs->dayover(L"-zaczynanie dnia od picia kawy\n"
						L"-sprawdzanie wytycznych\n"
						L"-logowanie do systemu\n"
						L"-korzystanie z pomocy dzia�u IT\n"
						L"-ochrona has�a\n"
						L"-odrzucanie za��cznik�w nieznanych �r�de�\n");
					gs->nextDay = true;
				}
			}

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
	ITguy->draw(win);

	win.display();
}