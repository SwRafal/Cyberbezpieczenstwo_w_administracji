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
				gs->choice1->setPosition(MOBILE_POS_X - 300, MOBILE_POS_Y - 90);
				gs->choice2->setPosition(MOBILE_POS_X - 150, MOBILE_POS_Y - 90);
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

		gs->officeApplicant->text.setTextString(L"Petent: Czeœæ! Marek dziœ nie w pracy?");
		gs->officeApplicant->addToQueue(L"Ja: Jego stanowisko zosta³o zajête.");
		gs->officeApplicant->addToQueue(L"Petent: Szkoda, dobrze nam siê z nim pracowa³o…");
		gs->officeApplicant->addToQueue(L"Ja: Nie spe³nia³ wymogów bezpieczeñstwa. ");
		gs->officeApplicant->addToQueue(L"Petent: Wiesz co siê sta³o?");
		gs->officeApplicant->addToQueue(L"Ja: Nie mogê Ci tego powiedzieæ.");
		gs->officeApplicant->addToQueue(L"Petent: Có¿, witaj w naszym zespole. Masz, to dla Ciebie.");
		gs->officeApplicant->addToQueue(L"EOT");//Dodatkowa linijka potrzebna
		
		ITguy->text.setTextString(L"Tym Ciê pod³¹czymy do sieci.");
		ITguy->addToQueue(L"EOT");//Dodatkowa linijka potrzebna

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
				gs->gameover(L"Zasn¹³eœ w pracy! Pamiêtaj o kawie!");
				/*gs->lost = true;
				gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
				gs->gamelost_info = new sf::Text;
				gs->gamelost_info->setFont(*gm::Assets::getFont());
				gs->gamelost_info->setString(L"Zasn¹³eœ w pracy!\nPamiêtaj o kawie!");
				gs->gamelost_info->setCharacterSize(48);
				sf::Vector2f info_pos;
				info_pos.x = SCREEN_WIDTH / 2 - (gs->gamelost_info->getLocalBounds().left + gs->gamelost_info->getLocalBounds().width) / 2;
				info_pos.y = SCREEN_HEIGHT / 2 - (gs->gamelost_info->getLocalBounds().top + gs->gamelost_info->getLocalBounds().height) / 2;
				gs->gamelost_info->setPosition(sf::Vector2f(info_pos));*/
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

			if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				thought->closeBubble();
				finish_thought = true;
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

			if(gs->officeApplicant->state == 6)
				gs->sushi.setPosition(830, 400);

			if (gs->officeApplicant->state >= 7)
			{
				gs->officeApplicant->hide();
				finish_dialog = true;
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
				click_mobile = true;
				showButtons = true;
				gs->choice1->setText(L"Wyœlij");
				gs->choice2->setText(L"Nie wysy³aj");

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
					gs->mobile->text.setTextString(L"WYS£ANO!\nKoszt wiadomoœci to 450z³.");
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

				put_mobile = true;
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
				change_lines = true;
				state++;
			}
			else if (gs->openedcomputer->getState() == OpenPC::LOGIN_WIFI)
			{
				gs->gameover(L"Po³¹czy³eœ siê z internetem, nie zmieniwszy wczeœniej danych logowania!");
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
				gs->gameover(L"Nie zmieni³eœ has³a i ktoœ wkrad³ siê na konto!");
			}
			else if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD && gs->data->login != gs->data->name)
			{
				gs->openedcomputer->setState(OpenPC::SET_PASSWORD);
				thought->changeText(L"Login powinien byæ taki sam jak moje imiê...");
				thought->setBubblePosition(200, 100);
				thought->showBubble();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			}
			else if (gs->openedcomputer->getState() != OpenPC::SET_PASSWORD)
			{
				gs->data->login = gs->openedcomputer->getLogin();
				gs->data->password = gs->openedcomputer->getPassword();
				gs->computer->close();
			}
			if (!gs->computer->isOpened())
			{
				gs->officeLady->show();
				remember_password = true;
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

				gs->gameover(L"Firma sprz¹taj¹ca Ministerstwo znalaz³a twoje has³o do systemu!");
			}
			else if (gs->choice2->clicked(gm::Core::getWindow()))
			{
				showButtons = false;
				gs->officeLady->hide();
				write_down_password = true;
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

			if (gs->openedcomputer->show_communique)
			{
				showButtons = true;
				gs->choice1->setText(L"Pobierz");
				gs->choice2->setText(L"Anuluj");
				choose_wifi = true;
				state++;
			}
			else
			{
				if (!gs->computer->isOpened())
					gs->computer->update(win);
				if (gs->openedcomputer->getState() == OpenPC::DESKTOP)
				{
					gs->openedcomputer->setState(OpenPC::LOGIN_WIFI);
					thought->changeText(L"Czas pod³¹czyæ siê do sieci...");
					thought->setBubblePosition(200, 100);
					thought->showBubble();
					thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
				}
			}
			//gs->nextDay = true;

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
					refuse_wifi = true;
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
					gs->nagana_info->setString(L"Zainstalowa³eœ certyfikat z niepewnego Ÿród³a. Skontaktuj siê z dzia³em IT!");
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
					refuse_wifi = true;
					gs->openedcomputer->setState(OpenPC::DESKTOP);
					gs->computer->close();
					gs->openedcomputer->internet_works = true;
					state++;

					while (!gs->phone->text_queue.empty())
					{
						gs->phone->text_queue.pop();
					}

					gs->phone->addToQueue(L"Ja: Czeœæ tu " + gs->data->name + L"! Nie mogê po³¹czyæ siê z sieci¹, pomo¿ecie?");
					gs->phone->addToQueue(L"Pracownik dzia³u IT: Pomo¿emy!!!");
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
				phone_it = true;
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
					rj45 = true;
					state++;

					gs->computer->open();
					gs->openedcomputer->setState(OpenPC::MAIL);
					gs->openedcomputer->newMail(L"Passwordmanagers",L"dzia³IT@Mindswszelakich.pl", L"Szanowny urzêdniku!\nPamiêtaj, aby nigdy nie zapisywaæ swoich hase³ w miejscach, "
																									L"do których ktoœ nieupowa¿niony mo¿e mieæ dostêp.\n"
																									L"W Ministerstwie u¿ywamy specjalnego programu do zarz¹dzania has³ami, pobierz go z za³¹cznika poni¿ej i dok³adnie przeczytaj instrukcje.\n\n"
																									L"Za³¹cznik: Passmen.exe");
					showButtons = true;
					gs->choice1->setText(L"Pobierz");
					gs->choice2->setText(L"Odrzuæ");
				}
			}
			else if (ITguy->state >= 1)
			{
				ITguy->hide();
				gs->naganiony = true;
				gs->nagana_info = new sf::Text;
				gs->nagana_info->setFont(*gm::Assets::getFont());
				gs->nagana_info->setString(L"Dostêp do sieci przyznany!");
				gs->nagana_info->setFillColor(sf::Color::Green);
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
				gs->gameover(L"Pobra³eœ i zainstalowa³eœ zawirusowany za³¹cznik z nieautoryzowanego Ÿród³a. Twoje has³o do systemu zosta³o skradzione." 
							 L"W wyniku twoich dzia³añ dosz³o do wycieku danych Ministerstwa a jego wiarygodnoœæ zosta³a zrujnowana. Zostajesz zwolniony dyscyplinarnie w trybie natychmiastowym.");
			else if (gs->choice2->clicked(win))
			{
				while (!ITguy->text_queue.empty())
					ITguy->text_queue.pop();

				ITguy->text.setTextString(L"Pracownikom bez specjalnych uprawnieñ nie wolno samodzielnie instalowaæ ¿adnych programów.");
				ITguy->addToQueue(L"Programy z niezaufanych Ÿróde³ s¹ niebezpieczene.");
				ITguy->addToQueue(L"Dzia³ IT zajmie siê instalacj¹ potrzebnego ci oprogramowania.");
				ITguy->addToQueue(L"Istotnie dobrze jest tworzyæ i zapisywaæ has³a w menad¿erze hase³,");
				ITguy->addToQueue(L"wtedy s¹ one bezpieczne i musisz zapamiêtaæ tylko jedno has³o – do menad¿era.");
				ITguy->addToQueue(L"Na dziœ dziêkujemy mo¿esz wracaæ do domu.");
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
						L"-korzystanie z pomocy dzia³u IT\n"
						L"-ochrona has³a\n"
						L"-odrzucanie za³¹czników nieznanych Ÿróde³\n");
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