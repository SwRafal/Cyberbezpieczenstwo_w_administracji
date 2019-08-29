#include "GameState.h"
#include <thread>
#include "MenuState.h"

GameState::GameState(gm::gameDataRef data) : data(data)
{

}
GameState::~GameState()
{
	delete day0;
	day0 = nullptr;
	delete day1;
	day1 = nullptr;

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
	gm::Assets::EraseTexture("CALENDAR");
	gm::Assets::EraseTexture("WALL");
}

void GameState::init()
{
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

	//pc
	computer = new pc;

	gm::Assets::LoadTexture("friend", TEXTURE_OFFICE_FRIEND);
	gm::Assets::LoadTexture("chat bubble",TEXTURE_CHAT_BUBBLE);
	gm::Assets::LoadTexture("arrow",TEXTURE_ARROW_BUTTON);
	if(gm::Assets::getTexture("friend") == nullptr || gm::Assets::getTexture("chat bubble") == nullptr || gm::Assets::getTexture("arrow") == nullptr )
		error_win_close();
	else
	{
		officeLady = new OfficeFriend(gm::Assets::getTexture("friend"));
	}

	gm::Assets::LoadTexture("text bubble",TEXTURE_TEXT_BUBBLE);
	if(gm::Assets::getTexture("text bubble") == nullptr)
		error_win_close();
	else
	{
		popUpText = new textBubble(gm::Assets::getTexture("text bubble"));
	}

	/*Starting settings*/
	dayShowScreen = new dayx(this->data->day);
	initialized = false;
	nextDay = false;
	day = 0;


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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		officeLady->show();
		//test->showBubble();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		officeLady->hide();
		//test->closeBubble();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
		phone->call();

	if(gm::Core::getEnteredChar() == 0x0000007A)
	{
		nextDay = true;
	}

	
}

void GameState::update(sf::RenderWindow &win)
{
	//phone->update(win);
	calendar->update(win);
	computer->update(win);
	watch->update(gm::Core::getClock());

	if (book->isOpened())
	{
		if (openedbook->update(win))
			book->close();

		return;
	}

/*	yes_stamp->update(win);
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

	}*/


	dayShowScreen->update();
	popUpText->animate();
	officeLady->animate();
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
				officeLady->addToQueue(L"Czeœæ Halina!");
				officeLady->addToQueue(L"Mi³o mi Ciê poznaæ! Wiele o Tobie s³ysza³am");
				officeLady->addToQueue(L"Jestem zaszczycona, ¿e bêdê pracowaæ z takim ekspertem do spraw cyberbezpieczeñstwa!");
				officeLady->addToQueue(L"Pozwól, ¿e poka¿ê ci twoje miejsce pracy!");
				break;
			case 2:
				officeLady->addToQueue(L"Witaj! Powiedziano mi tylko, ¿e jesteœ wybitnym hakerem.");
			case 3:
				if(this->data->characterChoice != 2)
					officeLady->addToQueue(L"Witaj! Powiedziano mi tylko, ¿e jesteœ wybitnym magiem.");
				officeLady->addToQueue(L"Jak mam siê do Ciebie zwracaæ?");
				officeLady->addToQueue(L"Masz œwietne poczucie humoru! Cieszê siê, ¿e bêdziemy razem pracowaæ!");

				sf::String s = L"Mi³o mi Ciê poznaæ .";
				s = s + this->data->name + sf::String(L" Wiele o tobie s³ysza³am");

				officeLady->addToQueue(s);
				officeLady->addToQueue(L"Jestem zaszczycona, ¿e bêdê pracowaæ z takim ekspertem do spraw cyberbezpieczeñstwa!");
				officeLady->addToQueue(L"Pozwól, ¿e poka¿ê ci twoje miejsce pracy!");
				break;
			}

			choice1->setPosition(0,-300);
			choice2->setPosition(0,-300);

			choice1->setScale(0.37,0.37);
			choice2->setScale(0.37,0.37);

			choice1->setText(L"Ujawnij swoje dane osobowe");
			choice2->setText(L"Powo³aj siê na RODO");

			
			popUpText->changeText(L"Niestety RODO nie uchroni³o Ciê przed podaniem swoich danych osobowych.");
			popUpText->setBubblePosition(0,-300);

			officeLady->nextLine();
		}
		else if (day == 1)//Day1
		{
			eyelids->open();
			watch->setHour(8, 0);
			while (!phone->text_queue.empty())
			{
				phone->text_queue.pop();
			}
			phone->addToQueue(L"Czeœæ " + data->name + L"! Jestem z dzia³u IT. Twoje dane logowania to:\nUser: Admin\nHas³o: Admin");
			phone->addToQueue(L"Pamiêtaj, aby je zmieniæ po zalogowaniu!");

			openedbook->setInfoL(L"1. Zabezpiecz dane logowania");
			openedbook->setInfoR("");
		}


		initialized = true;
	}

	/* Days */
	if (day == 0)
		day0->update(this, win);
	else if (day == 1)
		day1->update(this, win);

	if(nextDay)
	{
		day++;
		nextDay = false;
		initialized = false;
		dayShowScreen->nextDay();
		this->data->day++;
		watch->setHour(8,0);
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

	/*Items*/
	std::priority_queue<gm::Button*, std::vector<gm::Button*>, ItemsComparator> button_items;
	button_items.push(book);
	button_items.push(coffee);
	button_items.push(yes_stamp);
	button_items.push(no_stamp);
	//button_items.push(phone);
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

	

	//tutorial
	officeLady->draw(win);

	if(day0->state == 2)
	{
		choice1->draw(win);
		choice2->draw(win);
	}


	dayShowScreen->draw(win,sf::RenderStates::Default);

	win.draw(*textField);
	popUpText->draw(win);

	eyelids->draw(win);
	if (lost)
		win.draw(*gamelost_info);
	
	
	if (day0->part1Over && day == 0)
		day0->draw(this);
	else if (day == 1)
		day1->draw(this, win);
	else
	win.display();
}