#include "GameState.h"
#include <thread>
#include "MenuState.h"

GameState::GameState(gm::gameDataRef data) : data(data),playerIco(data->characterChoice)
{

}
GameState::~GameState()
{
	delete day0;
	day0 = nullptr;
	delete day1;
	day1 = nullptr;
	delete day2;
	day2 = nullptr;
	delete day3;
	day3 = nullptr;

	delete eyelids;

	delete calendar;
	calendar = nullptr;
	delete watch;
	watch = nullptr;
	delete coffee;
	coffee = nullptr;
	delete battery;
	battery = nullptr;
	delete bell;
	bell = nullptr;
	delete yes_stamp;
	yes_stamp = nullptr;
	delete no_stamp;
	no_stamp = nullptr;
	delete book;
	book = nullptr;
	delete openedbook;
	openedbook = nullptr;
	delete officeApplicant;
	officeApplicant = nullptr;
	delete doc;
	doc = nullptr;
	delete open_doc;
	open_doc = nullptr;

	gm::Assets::EraseTexture("RJ45");
	gm::Assets::EraseTexture("SUSHI");
	gm::Assets::EraseTexture("BIN");
	gm::Assets::EraseTexture("BOOK");
	gm::Assets::EraseTexture("OPENEDBOOK");
	gm::Assets::EraseTexture("NOSTAMP");
	gm::Assets::EraseTexture("YESSTAMP");
	gm::Assets::EraseTexture("BELL");
	gm::Assets::EraseTexture("BATTERY");
	gm::Assets::EraseTexture("COFFEE");
	gm::Assets::EraseTexture("WATCH");
	gm::Assets::EraseTexture("TELEPHONE");
	gm::Assets::EraseTexture("PRIVATE_PHONE");
	gm::Assets::EraseTexture("CALENDAR");
	gm::Assets::EraseTexture("WALL");
	gm::Assets::EraseTexture("DOC");
	gm::Assets::EraseTexture("OPEN_DOC");
}

void GameState::init()
{
	data->password= L"Admin";

	//Wall
	gm::Assets::LoadTexture("WALL", TEXTURE_WALL);
	if (gm::Assets::getTexture("WALL") == nullptr)
		error_win_close();
	else
	{
		wall.setTexture(*gm::Assets::getTexture("WALL"));
		wall.setPosition(sf::Vector2f(0, 0));
	}

	//Desk
	gm::Assets::LoadTexture("DESK", TEXTURE_DESK);
	if (gm::Assets::getTexture("DESK") == nullptr)
		error_win_close();
	else
	{
		desk.setTexture(*gm::Assets::getTexture("DESK"));
		desk.setPosition(sf::Vector2f(0, 466));
	}

	//Calendar
	gm::Assets::LoadTexture("CALENDAR", TEXTURE_CALENDAR);
	if (gm::Assets::getTexture("CALENDAR") == nullptr)
		error_win_close();
	else
	{
		calendar = new Calendar(gm::Assets::getFont(), gm::Assets::getTexture("CALENDAR")/*,date*/);
	}

	//Watch
	gm::Assets::LoadTexture("WATCH", TEXTURE_WATCH);
	if (gm::Assets::getTexture("WATCH") == nullptr)
		error_win_close();
	else
	{
		watch = new Watch(gm::Assets::getFont(), gm::Assets::getTexture("WATCH"), 8, 0);
	}

	//Coffee
	gm::Assets::LoadTexture("COFFEE", TEXTURE_COFFEE);
	if (gm::Assets::getTexture("COFFEE") == nullptr)
		error_win_close();
	else
	{
		coffee = new Coffee(gm::Assets::getTexture("COFFEE"));
	}

	//Battery
	gm::Assets::LoadTexture("BATTERY", TEXTURE_BATTERY);
	if (gm::Assets::getTexture("BATTERY") == nullptr)
		error_win_close();
	else
	{
		battery = new Battery(gm::Assets::getTexture("BATTERY"));
	}

	//Bell
	gm::Assets::LoadTexture("BELL", TEXTURE_BELL);
	if (gm::Assets::getTexture("BELL") == nullptr)
		error_win_close();
	else
	{
		bell = new Bell(gm::Assets::getTexture("BELL"));
	}

	//YESstamp
	gm::Assets::LoadTexture("YESSTAMP", TEXTURE_YESSTAMP);
	if (gm::Assets::getTexture("YESSTAMP") == nullptr)
		error_win_close();
	else
	{
		yes_stamp = new Stamp(gm::Assets::getTexture("YESSTAMP"));
		yes_stamp->setPosition(yes_stamp_pos);
	}
	//NOstamp
	gm::Assets::LoadTexture("NOSTAMP", TEXTURE_NOSTAMP);
	if (gm::Assets::getTexture("NOSTAMP") == nullptr)
		error_win_close();
	else
	{
		no_stamp = new Stamp(gm::Assets::getTexture("NOSTAMP"));
		no_stamp->setPosition(no_stamp_pos);
	}

	//Book
	gm::Assets::LoadTexture("BOOK", TEXTURE_BOOK);
	if (gm::Assets::getTexture("BOOK") == nullptr)
		error_win_close();
	else
	{
		book = new Book(gm::Assets::getTexture("BOOK"));
	}

	//OpenedBook
	gm::Assets::LoadTexture("OPENEDBOOK", TEXTURE_OPENEDBOOK);
	if (gm::Assets::getTexture("OPENEDBOOK") == nullptr)
		error_win_close();
	else
	{
		openedbook = new OpenedBook(gm::Assets::getTexture("OPENEDBOOK"), gm::Assets::getFont());
	}

	//Bin
	gm::Assets::LoadTexture("BIN", TEXTURE_BIN);
	if (gm::Assets::getTexture("BIN") == nullptr)
		error_win_close();
	else
	{
		bin = new Bin(gm::Assets::getTexture("BIN"));
	}

	//phone
	phone = new Phone;

	//Private Phone
	gm::Assets::LoadTexture("MOBILE_VIEW", TEXTURE_MOBILE_VIEW);
	if (gm::Assets::getTexture("MOBILE_VIEW") == nullptr)
		error_win_close();
	gm::Assets::LoadTexture("PRIVATE_PHONE", TEXTURE_PRIVATE_PHONE);
	if (gm::Assets::getTexture("PRIVATE_PHONE") == nullptr)
		error_win_close();
	else
	{
		mobile = new Mobile(gm::Assets::getTexture("PRIVATE_PHONE"));
	}

	//DOCUMENT
	gm::Assets::LoadTexture("DOC", TEXTURE_DOC);
	if (gm::Assets::getTexture("DOC") == nullptr)
		error_win_close();
	else
	{
		doc = new Document(gm::Assets::getTexture("DOC"));
	}

	//OPENED DOCUMENT
	gm::Assets::LoadTexture("OPEN_DOC", TEXTURE_OPEN_DOC);
	if (gm::Assets::getTexture("OPEN_DOC") == nullptr)
		error_win_close();
	else
	{
		open_doc = new OpenedDoc(gm::Assets::getTexture("OPEN_DOC"), gm::Assets::getFont());
	}

	//pc
	computer = new pc;
	gm::Assets::LoadTexture("OPENEDCOMPUTER", TEXTURE_OPENEDCOMPUTER);
	if (gm::Assets::getTexture("OPENEDCOMPUTER") == nullptr)
		error_win_close();
	else
	{
		openedcomputer = new OpenPC(gm::Assets::getTexture("OPENEDCOMPUTER"), gm::Assets::getFont());
	}

	//card

	gm::Assets::LoadTexture("idCard", ID_CARD_TEXTURE);
	if (gm::Assets::getTexture("idCard") == nullptr)
		error_win_close();
	else
	{
		card = new Card(gm::Assets::getTexture("idCard"));
	}

	card->setPosition(-200,0);
	//card reader
	cardReader = new CardReader(card);


	gm::Assets::LoadTexture("friend", TEXTURE_OFFICE_FRIEND);
	gm::Assets::LoadTexture("chat bubble",TEXTURE_CHAT_BUBBLE);
	gm::Assets::LoadTexture("arrow",TEXTURE_ARROW_BUTTON);
	if(gm::Assets::getTexture("friend") == nullptr || gm::Assets::getTexture("chat bubble") == nullptr || gm::Assets::getTexture("arrow") == nullptr )
		error_win_close();
	else
	{
		officeLady = new OfficeApplicant(gm::Assets::getTexture("friend"));
		officeLady->move(0,7);
	}

	gm::Assets::LoadTexture("APPLICANT", TEXTURE_APPLICANT);
	if (gm::Assets::getTexture("APPLICANT") == nullptr)
		error_win_close();
	else
	{
		officeApplicant = new OfficeApplicant(gm::Assets::getTexture("APPLICANT"));
	}

	gm::Assets::LoadTexture("text bubble",TEXTURE_TEXT_BUBBLE);
	if(gm::Assets::getTexture("text bubble") == nullptr)
		error_win_close();
	else
	{
		popUpText = new textBubble(gm::Assets::getTexture("text bubble"));
	}

	//IT guy
	gm::Assets::LoadTexture("itGuy", IT_GUY_TEXTURE);
	if (gm::Assets::getTexture("itGuy") == nullptr)
		error_win_close();

	gm::Assets::LoadTexture("itGuyHand", IT_GUY_HAND_TEXTURE);
	if (gm::Assets::getTexture("itGuyHand") == nullptr)
		error_win_close();

	gm::Assets::LoadTexture("SUSHI", TEXTURE_SUSHI);
	if(gm::Assets::getTexture("SUSHI") == nullptr)
		error_win_close();
	else
	{
		sushi.setTexture(*gm::Assets::getTexture("SUSHI"));
		sushi.setScale(sf::Vector2f(0.3,0.3));
		sushi.setPosition(sf::Vector2f(-300, 0));
	}

	gm::Assets::LoadTexture("RJ45", TEXTURE_RJ45);
	if (gm::Assets::getTexture("RJ45") == nullptr)
		error_win_close();
	else
	{
		rj45.setTexture(*gm::Assets::getTexture("RJ45"));
		rj45.setPosition(sf::Vector2f(-300, 0));
	}

	/*Starting settings*/
	dayShowScreen = new dayx(this->data->day);
	initialized = false;
	nextDay = false;
	day = 0;
	data->day = day;


	choice1 = new ChoiceButton;
	choice2 = new ChoiceButton;
	choice3 = new ChoiceButton;
	choice4 = new ChoiceButton;

	textField = new gm::TextField(*gm::Assets::getFont());
	textField->setIdleColor(sf::Color::White);
	textField->setAimedColor(sf::Color(189, 189, 189,255));
	textField->setPressColor(sf::Color::White);
	textField->setSize(293,60);
	textField->setTextSize(25);
	textField->setTextString(L"");
	
	eyelids = new Eyelids;


	/* Days */
	day0 = new Day_0;
	day1 = new Day_1;
	day2 = new Day_2;
	day3 = new Day_3;

	
}

void GameState::handleInput()
{
		/*Events*/
		gm::Core::resetEvent();
		gm::Core::setEnteredChar(NULL);
		


		while (gm::Core::getWindow().pollEvent(gm::Core::getEvent()))
		{
			switch (gm::Core::getEvent().type)
			{
			case sf::Event::Closed:
				gm::Core::getWindow().close();
				break;
			case sf::Event::TextEntered:
				gm::Core::setEnteredChar(gm::Core::getEvent().text.unicode);
				break;
			}
		}

	if(gm::Core::getEnteredChar() == 0x0000001B)
	{
		//pause state		
		sf::Texture tex;
		tex.create(gm::Core::getWindow().getSize().x,gm::Core::getWindow().getSize().y);
		tex.update(gm::Core::getWindow());
		gm::Assets::LoadTextureFromImage("pause bg", tex.copyToImage());
		data->machine.addState(gm::StateRef(new PauseState (this->data)),false);      
	}
	if(data->returnToMenu == true)
	{
		data->returnToMenu = false;
		data->machine.addState(gm::StateRef(new MenuState (this->data))); 
	}
	

	if(gm::Core::getEnteredChar() == 0x0000007A)
	{
		nextDay = true;
	}

	
}

void GameState::update(sf::RenderWindow &win)
{
	playerIco.animate();
	
	calendar->update(win);
	watch->update(gm::Core::getClock());



	dayShowScreen->update();
	popUpText->animate();
	officeLady->animate();
	officeApplicant->animate();
	textField->update(gm::Core::getWindow(),gm::Core::getEnteredChar());
	eyelids->update();

	/* days management */

	/* Initialize day */
	if(!initialized)
	{
		if(day == 0) //intro
		{
			
			switch (this->data->characterChoice)
			{
			case 0:
				std::cout << "nie przeszedles intro ";
				break;
			case 1:
				officeLady->addToQueue(L"Cze�� Halina!");
				officeLady->addToQueue(L"Mi�o mi Ci� pozna�! Wiele o Tobie s�ysza�am");
				officeLady->addToQueue(L"Jestem zaszczycona, �e b�d� pracowa� z takim ekspertem do spraw cyberbezpiecze�stwa!");
				officeLady->addToQueue(L"Pozw�l, �e poka�� ci twoje miejsce pracy!");
				break;
			case 2:
				officeLady->addToQueue(L"Witaj! Powiedziano mi tylko, �e jeste� wybitnym hakerem.");
			case 3:
				if(this->data->characterChoice != 2)
					officeLady->addToQueue(L"Witaj! Powiedziano mi tylko, �e jeste� wybitnym magiem.");
				officeLady->addToQueue(L"Jak mam si� do Ciebie zwraca�?");
				officeLady->addToQueue(L"Masz �wietne poczucie humoru! Ciesz� si�, �e b�dziemy razem pracowa�!");

				sf::String s = L"Mi�o mi Ci� pozna� .";
				s = s + this->data->name + sf::String(L" Wiele o tobie s�ysza�am");

				officeLady->addToQueue(s);
				officeLady->addToQueue(L"Jestem zaszczycona, �e b�d� pracowa� z takim ekspertem do spraw cyberbezpiecze�stwa!");
				officeLady->addToQueue(L"Pozw�l, �e poka�� ci twoje miejsce pracy!");
				break;
			}

			choice1->setPosition(0,-300);
			choice2->setPosition(0,-300);
			choice3->setPosition(0,-300);
			choice4->setPosition(0,-300);

			choice1->setScale(0.37,0.37);
			choice2->setScale(0.37,0.37);
			choice3->setScale(0.37,0.37);
			choice4->setScale(0.37,0.37);

			choice1->setText(L"Ujawnij swoje dane osobowe");
			choice2->setText(L"Powo�aj si� na RODO");
			choice3->setText(L"Powo�aj si� na RODO");
			choice4->setText(L"Powo�aj si� na RODO");

			
			popUpText->changeText(L"Niestety RODO nie uchroni�o Ci� przed podaniem swoich danych osobowych.");
			popUpText->setBubblePosition(0,-300);

			officeLady->nextLine();
		}
		else if (day == 1)//Day1
		{
			eyelids->open();
			coffee->reset();
			computer->close();
			computer->turnOff();
			officeApplicant->state = 0;
			day1->ITguy->state = 0;
			openedcomputer->setState(OpenPC::USERS);
			data->login = "Admin";
			data->password = "Admin";
			openedcomputer->setLogin("Admin");
			openedcomputer->setPassword("Admin");
			watch->setHour(8, 0);
			while (!phone->text_queue.empty())
			{
				phone->text_queue.pop();
			}
			while (!officeLady->text_queue.empty())
			{
				officeLady->text_queue.pop();
			}

			phone->addToQueue(L"Cze�� " + data->name + L"! Jestem z dzia�u IT. Twoje dane logowania to:\nUser: Admin\nHas�o: Admin");
			phone->addToQueue(L"Pami�taj, aby je zmieni� po zalogowaniu!");

			mobile->text.setTextString( L"Nadawca: 7780\n\n"
										L"Gratulujemy! Jeste� jednym z 10 szcz�liwc�w maj�cych szans� na wygranie XMobile15 lub XTab Pro sponsorowanych"
										L"przez naszych partner�w. Liczba prezent�w jest ograniczona, decyduje kolejno�� zg�osze�. Aby otrzyma� prezent"
										L"wy�lij SMS o tre�ci JESTEM ZWYCIEZCA na numer 7780.");

			officeLady->text.setTextString(L"Mocne has�a ci�ko zapami�ta�, lepiej zapisz je na kartce. Ja tak robi�.");

			openedbook->setInfoL(L"1. Zabezpiecz dane logowania");
			openedbook->setInfoR("");
		}
		else if(day == 3)
		{
			eyelids->open();
			coffee->reset();
			computer->close();
			computer->turnOff();
			officeApplicant->state = 0;
			openedcomputer->setState(OpenPC::USERS);
			openedcomputer->setLogin(data->login);
			openedcomputer->setPassword(data->password);
			watch->setHour(8, 0);
			while (!phone->text_queue.empty())
			{
				phone->text_queue.pop();
			}
			while (!officeLady->text_queue.empty())
			{
				officeLady->text_queue.pop();
			}

			phone->addToQueue(L"Cze�� " + data->name + L"! Jestem z dzia�u IT. Twoje dane logowania to:\nUser: Admin\nHas�o: Admin");
			phone->addToQueue(L"Pami�taj, aby je zmieni� po zalogowaniu!");

			mobile->text.setTextString(L"Nadawca: 7780\n\n"
				L"Gratulujemy! Jeste� jednym z 10 szcz�liwc�w maj�cych szans� na wygranie XMobile15 lub XTab Pro sponsorowanych"
				L"przez naszych partner�w. Liczba prezent�w jest ograniczona, decyduje kolejno�� zg�osze�. Aby otrzyma� prezent"
				L"wy�lij SMS o tre�ci JESTEM ZWYCIEZCA na numer 7780.");

			officeLady->text.setTextString(L"To ty nie wiesz? Aniela wyrzuci�a swoje kartki z has�ami do �mieci. Na szcz�cie znale�li je pracownicy naszego ministerstwa.");
			officeLady->addToQueue(L"Wiedzia�e�? Istnieje co� takiego jak Trashing. Z�odzieje przeszukuj� �mieci firm, �eby zdoby� has�a czy inne warto�ciowe informacje.");
			officeLady->addToQueue(L"W �yciu bym nie wpad�a na to, �e kto� mo�e zdobywa� dane w ten spos�b. FUUUUUUUUUUUUJ.");
			officeLady->addToQueue(L"EOT");
		}


		initialized = true;
	}



	/* Days */
	if (day == 0)
		day0->update(this, win);
	else if (day == 1)
	{
		if (book->isOpened())
		{
			if (openedbook->update(win))
				book->close();
		}
		if (computer->isOpened())
		{
			if (openedcomputer->update(win))
				computer->close();

			data->login = openedcomputer->getLogin();
			data->password = openedcomputer->getPassword();
		}
		day1->update(this, win);
	}
	else if(day == 2)
	{
		if (book->isOpened())
		{
			if (openedbook->update(win))
				book->close();
		}
		if (computer->isOpened())
		{
			if (openedcomputer->update(win))
				computer->close();
		}

		card->update(win);
		cardReader->update();

		day2->update(this,win);
	}
	else if (day == 3)
	{
		if (book->isOpened())
		{
			if (openedbook->update(win))
				book->close();
		}
		if (computer->isOpened())
		{
			if (openedcomputer->update(win))
				computer->close();

			openedcomputer->getLogin() = data->login;
			openedcomputer->getPassword() = data->password;
		}
		day3->update(this, win);
	}
	else//W inne dni
	{
		if (book->isOpened())
		{
			if (openedbook->update(win))
				book->close();
			return;
		}
		if (computer->isOpened())
		{
			if (openedcomputer->update(win))
				computer->close();

			data->login = openedcomputer->getLogin();
			data->password = openedcomputer->getPassword();
			return;
		}

		computer->update(win);
		phone->update(win);

		yes_stamp->update(win);
		no_stamp->update(win);
		if (yes_stamp->getPosition().y < no_stamp->getPosition().y)
		{
			if (no_stamp->isActive())
				yes_stamp->setInactive();
		}
		else
		{
			if (yes_stamp->isActive())
				no_stamp->setInactive();

		}
		card->update(win);
	}

	if(nextDay)
	{
		day++;
		nextDay = false;
		initialized = false;
		dayShowScreen->nextDay();
		this->data->day++;
		watch->setHour(8,0);
		calendar->setDay(calendar->getDay() + 1);
	}
	
}

void GameState::draw(sf::RenderWindow& win)
{
	win.clear(sf::Color::Black);

	/*Background*/
	win.draw(wall);
	win.draw(desk);
	calendar->draw(win);
	bell->draw(win);
	watch->draw(win);
	cardReader->draw(win);
	doc->draw(win);
	//open_doc->draw(win);

	/*Items*/
	win.draw(sushi);
	
	std::priority_queue<gm::Button*, std::vector<gm::Button*>, ItemsComparator> button_items;
	button_items.push(book);
	button_items.push(coffee);
	button_items.push(yes_stamp);
	button_items.push(no_stamp);
	button_items.push(mobile);
	button_items.push(phone);
	button_items.push(card);
	//...more
	
	
	/*--------------------------------*/

	computer->draw(win);
	phone->draw(win);
	

	/*Drawing*/
	while (!button_items.empty())
	{
		win.draw(*button_items.top());
		button_items.pop();
	}

	bin->draw(win);
	battery->draw(win);

	if (book->isOpened())
		openedbook->draw(win);
	if (computer->isOpened())
		openedcomputer->draw(win);
	if (mobile->pickedUp)
		mobile->draw_view(win);


	//tutorial
	officeLady->draw(win);

	if(day0->state == 2)
	{
		choice1->draw(win);
		choice2->draw(win);
	}
	if(day == 1) //day1
	{
		choice1->draw(win);
		choice2->draw(win);

		win.draw(rj45);
	}


	dayShowScreen->draw(win,sf::RenderStates::Default);

	win.draw(*textField);
	popUpText->draw(win);

	eyelids->draw(win);
	if (lost)
		win.draw(*gamelost_info);
	if (naganiony)
		win.draw(*nagana_info);

	playerIco.draw(win);
	
	if (day0->part1Over && day == 0)
		day0->draw(this);
	else if (day == 1)
		day1->draw(this, win);
	else if (day == 2)
		day2->draw(this, win);
	else if (day == 3)
		day3->draw(this, win);
	else
	win.display();
}