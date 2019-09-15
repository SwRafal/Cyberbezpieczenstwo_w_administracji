#include "Day_2.h"
#include "GameState.h"

Day_2::Day_2()
{
 	itGuy = new OfficeApplicant(gm::Assets::getTexture("itGuy"));
	itGuy->move(0,10);
	offset = 20;
	itGuy->chat.move(offset,0);
	itGuy->text.move(offset,0);
	itGuy->button.move(offset,0);
	itGuy->img.move(offset,0);

	gm::Assets::LoadTexture("boss",BOSS_TEXTURE);
	boss = new OfficeApplicant(gm::Assets::getTexture("boss"));
	offset = 60;
	boss->chat.move(offset,0);
	boss->text.move(offset,0);
	boss->button.move(offset,0);
	boss->img.move(offset,0);
	

	thought = new textBubble(gm::Assets::getTexture("text bubble"));
	thought->changeText(L"Nie œpij w pracy!!!");
	thought->setBubblePosition(0,-300);
	

	state = -1;

	init = false;
	initDelay = false;

	coffeeClicked = false;
	bookOpened = false;

	//mobile phone text
	displayPhoneText  = false;
	
	bg.setTexture(*gm::Assets::getTexture("chat bubble"));
	bg.setPosition(540,500);
	bg.setScale(0.6,0.6);
	phoneText.setFont(*gm::Assets::getFont());
	phoneText.setCharacterSize(15);
	phoneText.setFillColor(sf::Color::Black);
	phoneText.setStyle(sf::Text::Style::Regular);
	phoneText.setString(L"Dzwoni numer prywatny...");
	phoneText.setPosition(545,520);

	//work phone text
	displayWorkPhoneText = false;
	bgWork.setTexture(*gm::Assets::getTexture("chat bubble"));
	bgWork.setTextureRect(sf::IntRect(bgWork.getGlobalBounds().width, 0, -bgWork.getGlobalBounds().width, bgWork.getGlobalBounds().height));
	bgWork.setPosition(PHONE_POS_X + PHONE_WIDTH ,PHONE_POS_Y);
	bgWork.setScale(0.6,0.6);
	workPhoneText.setFont(*gm::Assets::getFont());
	workPhoneText.setCharacterSize(15);
	workPhoneText.setFillColor(sf::Color::Black);
	workPhoneText.setStyle(sf::Text::Style::Regular);
	workPhoneText.setString(L"Zadzwoñ do dzia³u IT.");
	workPhoneText.setPosition(PHONE_POS_X + PHONE_WIDTH + 30 ,PHONE_POS_Y + 5);

	bool displayWorkPhoneText;
	sf::Sprite bgWork;
	sf::Text workPhoneText;

	thiefTex.loadFromFile("resources/textures/thief.png");
	thief.setTexture(thiefTex);
	thief.setPosition(799,90);

	showDarkScreen = false;
	darkScreen.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
	darkScreen.setFillColor(sf::Color(0,0,0,200));

	showButtons = false;


	blankInfo.setFont(*gm::Assets::getFont());
	blankInfo.setCharacterSize(30);
	blankInfo.setFillColor(sf::Color::Green);
	blankInfo.setString(L"Wys³ano");
	blankInfo.setPosition(SCREEN_WIDTH / 2 - blankInfo.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.35);

	showInfo = false;

	//info /quests
	photosSent = false;

	//pendrive
	gm::Assets::LoadTexture("pendrive", TEXTURE_PENDRIVE);
	pendrive.setTexture(*gm::Assets::getTexture("pendrive"));
	pendrive.setScale(0.6,0.6);

	gm::Assets::LoadTexture("office friend hand", TEXTURE_OFFICE_FRIEND_HAND);

}

Day_2::~Day_2()
{
	
}


void Day_2::update(GameState *gs, sf::RenderWindow &win)
{
	if(showButtons)
	{
		if (state == 24)//Put mobile
		{
			gs->choice1->setPosition(SCREEN_WIDTH / 2 - (gs->choice1->background.getGlobalBounds().width) - (gs->choice1->background.getGlobalBounds().width / 2) , SCREEN_HEIGHT / 2);
			gs->choice2->setPosition(SCREEN_WIDTH / 2 + (gs->choice2->background.getGlobalBounds().width) - (gs->choice2->background.getGlobalBounds().width / 2) , SCREEN_HEIGHT / 2);
		}
		else if(state == 27)
		{
			gs->choice1->setText(L"Wyœlij zdjêcia do Krysi.");
			gs->choice2->setText(L"Wyloguj siê i wróæ na swoje konto.");
			gs->choice1->setPosition(SCREEN_WIDTH / 2 - (gs->choice1->background.getGlobalBounds().width) - (gs->choice1->background.getGlobalBounds().width / 2) - 30,PC_OPENED_POS_Y + PC_OPENED_HEIGHT * 0.7);
			gs->choice2->setPosition(SCREEN_WIDTH / 2 + (gs->choice2->background.getGlobalBounds().width) - (gs->choice2->background.getGlobalBounds().width / 2) - 30,PC_OPENED_POS_Y + PC_OPENED_HEIGHT * 0.7);
		}
		else if(state == 28)
		{
			gs->choice2->setText(L"Wyloguj siê i wróæ na swoje konto.");
			gs->choice2->setPosition(SCREEN_WIDTH / 2 - gs->choice2->background.getGlobalBounds().width / 2 - 30,PC_OPENED_POS_Y + PC_OPENED_HEIGHT * 0.7);
		}
		else if(state == 33)
		{
			gs->choice1->setText(L"SprawdŸ");
			gs->choice2->setText(L"Od³ó¿ na biurko");
			gs->choice1->setPosition(SCREEN_WIDTH / 2 - (gs->choice1->background.getGlobalBounds().width) - (gs->choice1->background.getGlobalBounds().width / 2) , SCREEN_HEIGHT / 2);
			gs->choice2->setPosition(SCREEN_WIDTH / 2 + (gs->choice2->background.getGlobalBounds().width) - (gs->choice2->background.getGlobalBounds().width / 2) , SCREEN_HEIGHT / 2);
		}
		else if(state == 34)
		{
			gs->choice1->setText(L"SprawdŸ plik z\npotwierdzeniem nadania");
			gs->choice2->setText(L"Zadzwoñ na numer Biura\nObs³ugi Klienta");
			gs->choice3->setText(L"Skonsultuj siê z kole¿ank¹");

			gs->choice1->setPosition(252 + 60 , 112 + 494 );
			gs->choice2->setPosition(252 + 60 + 50 + gs->choice2->background.getGlobalBounds().width , 112 + 494 );
			gs->choice3->setPosition(252 + 60 + 100 + gs->choice2->background.getGlobalBounds().width * 2, 112 + 494 );
		}
		else if(state == 38)
		{
			gs->choice1->setText(L"SprawdŸ kurierexpol\nw internecie");
			gs->choice2->setText(L"Zadzwoñ na numer Biura\nObs³ugi Klienta");

			gs->choice1->setPosition(252 + 10 + 50 + gs->choice2->background.getGlobalBounds().width , SCREEN_HEIGHT / 2 );
			gs->choice2->setPosition(252 + 10 + 100 + gs->choice2->background.getGlobalBounds().width * 2,SCREEN_HEIGHT / 2 );
		}
		else if(state == 39)
		{
			gs->choice1->setText(L"Usuñ maila od kurierexpol");
			gs->choice2->setText(L"Skontaktuj siê z dzia³em IT");

			gs->choice1->setPosition(252 + 10 + 50 + gs->choice2->background.getGlobalBounds().width , 112 + 494 - 20 );
			gs->choice2->setPosition(252 + 10 + 100 + gs->choice2->background.getGlobalBounds().width * 2, 112 + 494 - 20 );
		}
		else if(state == 43)
		{
			gs->choice1->setText(L"Zatrzymaj kole¿ankê i\noddaj pendrive");
			gs->choice2->setText(L"zajmij siê pendrivem");

			gs->choice1->setPosition(252 + 10 + 50 + gs->choice2->background.getGlobalBounds().width , 112 + 494 - 20 );
			gs->choice2->setPosition(252 + 10 + 100 + gs->choice2->background.getGlobalBounds().width * 2, 112 + 494 - 20 );
		}
		else if(state = 45)
		{
			gs->choice1->setText(L"SprawdŸ pendrive");
			gs->choice2->setText(L"Oddaj pendrive do dzia³u IT");

			gs->choice1->setPosition(252 + 10 + 50 + gs->choice2->background.getGlobalBounds().width , 112 + 494 - 20 );
			gs->choice2->setPosition(252 + 10 + 100 + gs->choice2->background.getGlobalBounds().width * 2, 112 + 494 - 20 );
		}
	}
	else
	{
		gs->choice1->setPosition(0,-300);
		gs->choice2->setPosition(0,-300);
		gs->choice3->setPosition(0,-300);
	}


	if(!init)
	{
		

		gs->coffee->reset();

		time = gm::Core::getClock().getElapsedTime().asSeconds();
		

		sf::String s = L"Czeœæ ";
		s = s + gs->data->name + "!";

		itGuy->text.setTextString(s);
		itGuy->addToQueue(L"W³aœnie skoñczyliœmy instalacjê potrzebnego ci oprogramowania. Jesteœ ju¿ zalogowany na swoje konto.");
		itGuy->addToQueue(L"Od teraz do wszystkich wewnêtrznych serwisów Ministerstwa, wymagaj¹cych has³a u¿ywasz menad¿era hase³.");
		itGuy->addToQueue(L"Ustawione przez ciebie wczoraj has³o, jest has³em do menad¿era.");
		itGuy->addToQueue(L"Mo¿esz zaczynaæ pracê. \nMi³ego dnia.");
		itGuy->addToQueue(L" ");
		
		gs->openedbook->setInfoR(L"2 Uwierzytelnianie dwusk³adnikowe.");

		s = L"Witaj ";
		s = s + gs->data->name + "!";
		boss->text.setTextString(s);
		boss->addToQueue(L"Nasze Ministerstwo bierze udzia³ w konkursie na najbezpieczniejsze ministerstwo œwiata.");
		boss->addToQueue(L"Od dziœ ka¿de logowanie musi byæ dwusk³adnikowe. Dalsze instrukcje w emailu.");
		boss->addToQueue(L" ");
		boss->state = 0;

		boss->move(0,11);

		gs->officeLady->text.setTextString(L"Dosta³am naganê za zapisywanie hase³ na kartkach. Jeszcze jedna wtopa i wylatujê.");
		gs->officeLady->addToQueue(L" ");
		gs->officeLady->state = 0;

		

		
		init = true;
	}

	if(!initDelay)
	{
		//tutaj !!!!
		state = 31;
		initDelay = true;
		//tutaj wyjebac
		if(gm::Core::getClock().getElapsedTime().asSeconds() - time >= 5)
		{
			state = 0;
			initDelay = true;

			itGuy->show();
		}

		gs->choice3->clicked(gm::Core::getWindow());
		gs->choice4->clicked(gm::Core::getWindow());
	}

	

	switch (state)
	{
	case 0: //gosc z it wbija
		itGuy->animate();

		
		if(itGuy->state == 5)
			itGuy->hide();

		if(itGuy->getPosition().x == 1390)
			state = 1;
		

		break;
	case 1: //drink coffee
		if (gs->coffee->update_drunk(win))
		{
			gs->battery->setActivation(true);
			coffeeClicked = true;
			state = 3;
			gs->book->setFillColor(sf::Color(230, 230, 230));
		}
		else if (gs->book->clicked(win) || gs->bell->clicked(win) || gs->bin->clicked(win) || gs->no_stamp->clicked(win) || gs->yes_stamp->clicked(win) || gs->computer->clicked(win))
		{
			gs->data->nagany++;
			thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			thought->showBubble();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			state++;
		}
		thought->animate();
		break;
	case 2: //nie spij w pracy
		thought->animate();
		if (thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state = 1;
		}
		break;
	case 3: //read book
		gs->book->update(win);
		gs->openedbook->update(win);

		if(gs->book->isOpened())
			bookOpened = true;

		
		if(bookOpened && !gs->book->isOpened())
			state++;

		break;
	case 4: //wpada szefu
		boss->show();
		state++;
		break;
	case 5:
		boss->animate();
		if(boss->state == 3)
			boss->hide();

		if(boss->getPosition().x == 1390)
		{
			gs->playerIco.text.setTextString(L"co siê sta³o?");
			gs->playerIco.state = 0;
			gs->playerIco.show();
			gs->officeLady->state = 0;
			gs->officeLady->show();
			state++;
		}
		break;
	case 6: //wpada ziomalka
		
		if(gs->officeLady->state == 1)
		{
			gs->officeLady->hide();
			gs->playerIco.hide();
		}
		if(gs->officeLady->hidden)
			state++;
		break;
	case 7: //wpada mail z it
		gs->computer->open();
		gs->openedcomputer->newMail(L"Silne uwierzytelnianie",L"IT@mdsw.gov.pl",L"Ochrona poufnoœci danych jest naszym priorytetem. Musimy zastosowaæ co najmniej dwa elementy nale¿¹ce do kategorii: \n1 Wiedza (czyli coœ o czym wiesz tylko Ty). \n2 Posiadanie (coœ co tylko Ty posiadasz). \n3 Cechy charakterystyczne u¿ytkownika. \nElementy te s¹ integraln¹ czêœci¹ uwierzytelnienia - Naruszenie jednego z nich nie os³abia ochrony gwarantowanej przez pozosta³e. \nWiedzê o danych logowania ju¿ masz. \nPrywatnie mo¿esz wybraæ z jakiego urz¹dzenia dodatkowego chcesz korzystaæ: SMS, TOKEN, LISTA HASE£ (AKA ZDRAPKA), Generator hase³ jednorazowych w twoim telefonie, s³u¿bowym, Karta kryptograficzna, Odcisk palca. \nAle my w ministerstwie wybraliœmy za ciebie. Otrzymujesz kartê s³u¿bow¹ – musisz ni¹ potwierdzaæ ka¿de logowanie do systemu. Dbaj o ni¹. ");
		gs->openedcomputer->setState(OpenPC::MAIL);
		state++;
		break;
	case 8: //zamykanie kompa
		if(gs->openedcomputer->getState() != OpenPC::MAIL)
		{
			gs->computer->close();
			state++;
		}
		break;
	case 9: //gosc it init
		delete itGuy;
		itGuy = new OfficeApplicant(gm::Assets::getTexture("itGuyHand"));
		itGuy->move(0,10);
		offset = 70;
		itGuy->chat.move(offset,0);
		itGuy->text.move(offset,0);
		itGuy->button.move(offset,0);
		itGuy->img.move(offset,0);
		itGuy->state = 0;
		itGuy->text.setTextString(L"Proszê, oto twoja karta. Pilnuj jej nale¿ycie.");
		itGuy->addToQueue(L" ");
		itGuy->show();
		state++;
		break;
	case 10:
		itGuy->animate();
		
		gs->card->setPosition(itGuy->getPosition().x - 45,290);
		gs->cardReader->hidden = false;
		if(itGuy->state > 0)
		{
			itGuy->hide();
			state++;
		}
		break;
	case 11:
		gs->mobile->update(gm::Core::getWindow());
		
		if(itGuy->hidden)
			state++;

		itGuy->animate();
		break;
	case 12:
		gs->mobile->update(gm::Core::getWindow());
		gs->mobile->pickedUp = false;
		gs->mobile->call();
		state++;
		break;
	case 13:
		gs->mobile->update(gm::Core::getWindow());
		if(gs->cardReader->isCardInside())
		{
			state = 21;
			break;
		}
		if(gs->mobile->aimed(win))
		{
			displayPhoneText = true;
		}
		else
			displayPhoneText = false;

		if(gs->mobile->pickedUp)
		{
			gs->mobile->pickedUp = false;
			//gs->card->setPosition(0,520);
			state++;
		}
		break;
	case 14: //odebranie telefonu 
		//init text
		displayPhoneText = false;
		thought->setBubblePosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		thought->changeText(L"Dzieñ dobry, tu sklep zoologiczny...");
		thought->showBubble();
		state++;
		break;
	case 15:
		thought->animate();
		if(thought->showText)
		{
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			state++;
		}
		break;
	case 16:
		thought->animate();
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->changeText(L"bla...");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 500;
			state++;
		}
		break;
	case 17:
		thought->animate();
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->changeText(L"bla bla...");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 1000;
			state++;
		}
		break;
	case 18:
		thought->animate();
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			gs->card->setPosition(-300,520);
			thought->changeText(L"bla bla bla...");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			state++;
		}
		break;
	case 19:
		thought->animate();
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			thought->closeBubble();
			state++;
		}
		break;
	case 20:
		thought->animate();
		if(!thought->appearing && !thought->disappearing)
		{
			gs->lost = true;
			gs->eyelids->close();
			gs->info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + GAMELOST_INFO_TIME;
			gs->gamelost_info = new sf::Text;
			gs->gamelost_info->setFont(*gm::Assets::getFont());
			gs->gamelost_info->setString(L"    Nie pilnowa³eœ nale¿ycie swojej karty uwierzytelniaj¹cej.\nSkradziona karta umo¿liwi³a kradzie¿ funduszy Ministerstwa.\nZostajesz zwolniony dyscyplinarnie w trybie natychmiastowym.");
			gs->gamelost_info->setCharacterSize(48);
			sf::Vector2f info_pos;
			info_pos.x = SCREEN_WIDTH / 2 - (gs->gamelost_info->getLocalBounds().left + gs->gamelost_info->getLocalBounds().width) / 2;
			info_pos.y = SCREEN_HEIGHT / 2 - (gs->gamelost_info->getLocalBounds().top + gs->gamelost_info->getLocalBounds().height) / 2;
			gs->gamelost_info->setPosition(sf::Vector2f(info_pos));

			//gs->data->returnToMenu = true;
		}
	case 21: //init friend
		gs->officeLady->state = 0;
		temp = L"Hej ";
		temp = temp + gs->data->name + L"!!!";
		gs->officeLady->text.setTextString(temp);
		gs->officeLady->addToQueue(L"Dzwoni³a do mnie Krysia, twoja poprzedniczka. Odchodz¹c z pracy zapomnia³a zgraæ swoich zdjêæ z ministerialnego œledzika.");
		gs->officeLady->addToQueue(L"Czy móg³byœ jej wys³aæ te zdjêcia? Has³o do jej konta to: krysia123");
		gs->officeLady->addToQueue(L"Dziêki.");
		gs->officeLady->addToQueue(L" ");
		gs->playerIco.text.setTextString(L"Ok ju¿ siê lecê siê wylogowaæ i zaraz sprawdzê konto Krysi");
		gs->officeLady->show();
		state++;
		break;
	case 22:
		if(gs->officeLady->state == 3)
		{
			gs->playerIco.show();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 2000;
		}
		if(gs->officeLady->state == 4 && thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			gs->officeLady->state = 0;
			gs->officeLady->hide();
			gs->playerIco.hide();
		}
		if(gs->officeLady->hidden)
			state++;
		break;
	case 23: //choice init
		gs->choice1->setText(L"Skontaktuj siê z dzia³em IT");
		gs->choice2->setText(L"Zaloguj siê na konto Krysi");
		showButtons = true;
		state++;
		break;
	case 24: //choice
		if(gs->choice1->clicked(win)) // it
		{
			showButtons = false;
			state = 25;
		}
		if(gs->choice2->clicked(win)) //wyslij
		{
			showButtons = false;
			state = 26;
		}
		break;
	case 25:
		if(gs->phone->clicked(win))
		{
			while(!gs->phone->text_queue.empty())
				gs->phone->text_queue.pop();
			gs->playerIco.state = 0;
			gs->playerIco.text.setTextString(L"Czeœæ, dzwoni³a do mnie kole¿anka by³ej pracownicy Krysi, chcia³a uzyskaæ dostêp do jej konta.");
			gs->playerIco.addToQueue(L"Czy konta by³ych pracowników powinny byæ ci¹gle aktywne i dostêpne?");
			gs->playerIco.addToQueue(L"Dzia³ IT nie pracuje tu najsprawniej...");
			

			gs->phone->text.setTextString(L"Masz racje – nie powinny. Nasz b³¹d. Powinniœmy zabezpieczyæ te konta i znajduj¹ce siê na nich dane");
			gs->phone->addToQueue(L"Do jutra zostanie to naprawione. Skontaktujemy siê te¿ z Krysi¹.");
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 4000;
			gs->playerIco.show();
			gs->openedcomputer->showExcessUsers = false;
			state = 30;
			break;
		}
		if(gs->phone->aimed(win))
		{
			displayWorkPhoneText = true;
		}
		else
			displayWorkPhoneText = false;
		break;
	case 26://pc choice + init
		if(gs->openedcomputer->getState() == OpenPC::DESKTOP_KRYSIA)
		{
			state++;
			break;
		}
		gs->openedcomputer->krysiaPasswordKnown = true;
		gs->computer->open();
		gs->openedcomputer->setState(OpenPC::USERS);
		
		break;
	case 27: //buttons
		showButtons = true;
		gs->openedcomputer->setExitButtonInactive();

		if(gs->choice1->clicked(win)) //wyslij
		{
			photosSent = true;
			showInfo = true;
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			gs->choice1->setPosition(0,-300);
			state++;
		}

		if(gs->choice2->clicked(win)) //wyloguj
		{
			showButtons = false;
			gs->computer->close();
			state = 29;
		}
		
		break;
	case 28:
		if(gm::Core::getClock().getElapsedTime().asMilliseconds() > thought_time)
			showInfo = false;

		if(gs->choice2->clicked(win))
		{
			showInfo = false;
			gs->computer->close();
			showButtons = false;
			state++;
		}
			
		break;
	case 29:
		gs->openedcomputer->setExitButtonActive();
		gs->openedcomputer->krysiaPasswordKnown = false;
		state = 31; //kolejny quest
		break;
	case 30:
		displayWorkPhoneText = false;
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			gs->playerIco.nextLine();
			displayWorkPhoneText = false;
			gs->phone->showText = true;
			gs->phone->pickedUp = true;
			state++;
		}
		break;
	case 31:
		gs->phone->update(win);
		
		if(!gs->phone->pickedUp)
		{
			if(!singleActivity)
			{
				gs->playerIco.nextLine();
				thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 2500;
				singleActivity = true;
			}
			if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
			{
				delete gs->officeLady;
				gs->officeLady = new OfficeApplicant(gm::Assets::getTexture("office friend hand"));
				gs->officeLady->move(0,8);
				gs->officeLady->moveChatBox(0,8);
				gs->officeLady->state = 0;
				gs->officeLady->text.setTextString(L"Janek z pokoju 102 znalaz³ dziœ pod drzwiami gabinetu tego pendrive'a.");
				gs->officeLady->addToQueue(L"Na pewno wypad³ jego koledze z pokoju, który wczoraj wyjecha³ na urlop.");
				gs->officeLady->addToQueue(L"Bartek sprawdza³, ale u niego na komputerze nic siê nie otwiera, u mnie i u Joli te¿ nie.");
				gs->officeLady->addToQueue(L"Nie chcemy zawracaæ g³owy ch³opakom z IT.");
				gs->officeLady->addToQueue(L"SprawdŸ proszê co na tym jest, bo mo¿e to byæ coœ istotnego. Dziêki. ");
				gs->officeLady->addToQueue(L" ");
				gs->officeLady->show();
				state++;
			}
			
		}
		break;
	case 32:
		gs->playerIco.hide();

		pendrive.setPosition(gs->officeLady->getPosition().x + 25,gs->officeLady->getPosition().y + 280);
		if(gs->officeLady->state == 5)
		{ //choice
			gs->choice1->setText(L"SprawdŸ");
			gs->choice2->setText(L"Od³ó¿ na biurko");
			showButtons = true;
			state++;
		}
		break;
	case 33:
		gs->officeLady->animate();
		if(gs->choice1->clicked(win))
		{
			showButtons = false;
			//przegrana
		}
		if(gs->choice2->clicked(win))
		{
			showButtons = false;
			pendrive.setPosition(650,620);
			gs->officeLady->hide();
			//inicjacja maila

			gs->computer->open();
			gs->openedcomputer->setState(OpenPC::MAIL);
			gs->openedcomputer->newMail(L"Powiadomienie o planowanej wizycie kuriera.",L"no-reply@kurierexpol.pl", L"Wiadomoœæ wygenerowana automatycznie. Prosimy nie odpowiadaæ bezpoœrednio na ten adres e-mail.\nSzanowni Pañstwo, Uprzejmie informujemy, ¿e w dniu dzisiejszym zostanie do Pañstwa dostarczona przesy³ka o numerze: 9847697300141\nW za³¹czniku szczegó³owe potwierdzenie nadania paczki. Has³em potrzebnym do otwarcia potwierdzenia jest numer twojej przesy³ki.KURIEREXPOL – Twój kurier na zawsze\n\nwww.kurierexpol.pl\nBiuro Obs³ugi Klienta\n+48 565 234 234\nZa³¹cznik: Potwierdzenienadania.pdf");
			showButtons = true;
			gs->openedcomputer->setMailButtonInactive();
			//setup buttons
			

			state++;
		}
		break;
	case 34:
		if(gs->officeLady->hidden)
		{
			if(gs->choice1->clicked(win)) //lose
			{
				showButtons = false;
				gs->computer->close();
				state++;
			}
			if(gs->choice2->clicked(win)) //lose
			{
				showButtons = false;
				gs->computer->close();
				state = 36;
			}
			if(gs->choice3->clicked(win)) //konsultacja
			{
				showButtons = false;
				gs->computer->close();
				gs->playerIco.text.setTextString(L"Czy zamawialiœmy coœ z Kurierexpol?");
				gs->playerIco.show();
				gs->officeLady->state = 0;
				gs->officeLady->text.setTextString(L"Nie wiem. Mo¿e skontaktuj siê z ich biurem obs³ugi.");
				gs->officeLady->addToQueue(L" ");
				gs->officeLady->show();
				state = 37;
			}
		}
		break;
	case 35: //przegrana po sprawdzeniu pliku

		break;
	case 36://przegrana po zadzwonieniu do kurierexpol

		break;
	case 37: //prawidlowa sciezka , rozmowa z kolezanka
		if(gs->officeLady->state == 1)
		{
			gs->officeLady->hide();
			gs->playerIco.hide();
			state++;
		}
		break;
	case 38: //prawidlowa sciezka v2
		showButtons = true;
		if(gs->choice1->clicked(win))
		{ //prawidlowa sciezka
			gs->computer->open();
			gs->openedcomputer->setState(OpenPC::INFO_DISPLAY);
			state++;
		}
		if(gs->choice2->clicked(win))
		{ //lose
			state = 36;	
		}
		break;
	case 39:
		gs->openedcomputer->setExitButtonInactive();
		if(gs->choice1->clicked(win))
		{
			gs->openedcomputer->setExitButtonActive();
			showButtons = false;
			state = 41;
			gs->computer->close();
			//nagana
		}
		if(gs->choice2->clicked(win))
		{
			gs->openedcomputer->setExitButtonActive();
			gs->phone->text.setTextString(L"Kurierexpol przedra³ siê przez nasze filtry?!");
			gs->phone->addToQueue(L"Dziêki za informacjê wysy³am grupê ratunkow¹. Bez odbioru.");
			gs->playerIco.text.setTextString(L"W³aœnie dosta³em maila od Kurierexpol. W gazetach pisz¹, ¿e to atak phishingowy...");
			state++;
			showButtons = false;
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			gs->playerIco.show();
			gs->computer->close();
			//rozmowa z it
		}
		break;
	case 40:
		
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			gs->phone->showText = true;
			gs->phone->pickedUp = true;
			gs->phone->update(win);
			if(!gs->phone->pickedUp)
			{
				gs->playerIco.hide();
				state++;
			}
		}
		break;
	
	case 41:
		gs->officeLady->state = 0;
		gs->officeLady->text.setTextString(L"Hej! Ja tylko na sekundkê.");
		gs->officeLady->addToQueue(L"Pamiêta³eœ, ¿eby sprawdziæ co jest na tym pendrive?");
		gs->officeLady->addToQueue(L"Nie? Nie zapomnij tego zrobiæ, proszê. Lecê dalej, paaa!");
		gs->officeLady->show();
		state++;
	break;
	case 42:
		if(gs->officeLady->state == 2)
		{
			showButtons = true;
			state++;
		}
		break;
	case 43: //zatrzymaj kolezanke?
		if(gs->choice1->clicked(win))
		{
			showPendrive = false;
			gs->playerIco.text.setTextString(L"Przepraszam, nie mam czasu siê dziœ tym zaj¹æ.");
			gs->playerIco.show();
			thought_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + THOUGHT_TIME;
			showButtons = false;
			state++;
		}
		if(gs->choice2->clicked(win))
		{
			gs->officeLady->hide();
			state = 45;
		}
		break;
	case 44:
		if(thought_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			gs->playerIco.hide();
			gs->officeLady->hide();
			//nagana i koniec dnia
		}
		break;
	case 45: //another choice
		if(gs->choice1->clicked(win))
		{
			//lose
			showButtons = false;
		}
		if(gs->choice2->clicked(win))
		{
			gs->phone->text.setTextString(L"Tu dzia³ IT, w czym mogê pomóc?");
			gs->phone->addToQueue(L"Ok zaraz po niego wpadnê. Nie pod³¹czaj go do komputera.");
			gs->playerIco.text.setTextString(L" Mam tu znalezionego na korytarzu pendrive. Mo¿ecie go sprawdziæ?");
			gs->phone->showText = true;
			gs->phone->pickedUp = true;
			gs->playerIco.show();
			showButtons = false;
			state++;
		}
		break;
	case 46:
		gs->phone->update(win);
		if(!gs->phone->pickedUp)
		{
			gs->playerIco.hide();
			state++;
		}
		break;
	case 47: //przychodzi janusz haker

		break;
	}
	

	
}

void Day_2::draw(GameState *gs, sf::RenderWindow &win)
{
	itGuy->draw(win);
	thought->draw(win);
	boss->draw(win);

	if(state== 10 || state == 11)
		win.draw(*gs->card);

	if(displayPhoneText)
	{
		win.draw(bg);
		win.draw(phoneText);
	}

	if(displayWorkPhoneText)
	{
		win.draw(bgWork);
		win.draw(workPhoneText);
	}

	if(state == 17 || state == 18)
		win.draw(thief);

	if(state > 31 && showPendrive)
	{
		if(!gs->computer->isOpened())
			win.draw(pendrive);
	}
		

	if(state == 24 || state == 33 || state == 38 || state == 43 || state == 45)
	{
		win.draw(darkScreen);
		gs->choice1->draw(win);
		gs->choice2->draw(win);
	}
	if(state == 27 || state == 28 || state == 39 )
	{
		gs->choice1->draw(win);
		gs->choice2->draw(win);
	}
	if(state == 34)
	{
		gs->choice1->draw(win);
		gs->choice2->draw(win);
		gs->choice3->draw(win);
	}



	if(showInfo)
		win.draw(blankInfo);

	win.display();
}
