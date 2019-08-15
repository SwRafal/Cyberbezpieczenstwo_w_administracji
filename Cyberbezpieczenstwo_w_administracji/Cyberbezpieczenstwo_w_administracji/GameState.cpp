#include "GameState.h"
#include <thread>
#include "MenuState.h"

GameState::GameState(gm::gameDataRef data) : data(data)
{

}
GameState::~GameState()
{
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

	//Telephone
	//gm::Assets::LoadTexture("TELEPHONE", TEXTURE_TELEPHONE);
	//if (gm::Assets::getTexture("TELEPHONE") == nullptr)
		//error_win_close();

	/*Starting settings*/
	//...

	dayShowScreen = new dayx(this->data->day);


	gm::Assets::LoadTexture("text bubble",TEXTURE_TEXT_BUBBLE);
	test = new textBubble(gm::Assets::getTexture("text bubble"));
	
	test->changeText(L"Maciekdsadas  dasdasiudjsaioudjasiduahsjdiuash duoashdoasuydghasuoiydhasouidhasio dyhasouydiahs sda dasdsadhasjuidh asiuhdiasudhasiu dhasi saoidjhsaioudjsaioud jhasioudhiasu hdiasudhiuash diuasdhio ddsidsiuahdi hsiaudhuias dhsa");
	test->setBubblePosition(300,400);

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
		test->showBubble();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		test->closeBubble();
}

void GameState::update(sf::RenderWindow &win)
{
	if (book->isOpened())
	{
		if (openedbook->update(win))
			book->close();

		return;
	}

	calendar->update(win);
	watch->update(gm::Core::getClock());

	if (!yes_stamp->isActive() && !no_stamp->isActive())
	{
		if (coffee->update_drunk(win))
		{
			battery->setLevel(battery->getLevel() + 20);
		}
		if (battery->update_empty(gm::Core::getClock()))
		{
			//GameOver
		}
		book->update(win);

		if (bell->update_rung(win))
		{
			//Call the client
		}

		if (true/*œmieæ podniesiony*/)
		{
			if (bin->clicked(win))
				;//Œmieæ znika
		}
	}

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
	dayShowScreen->update();
	test->animate();
}

void GameState::draw(sf::RenderWindow& win)
{
	win.clear(sf::Color::Black);

	/*Background*/
	win.draw(wall);
	calendar->draw(win);
	bell->draw(win);
	watch->draw(win);

	/*Items*/
	std::priority_queue<gm::Button*, std::vector<gm::Button*>, ItemsComparator> button_items;
	button_items.push(book);
	button_items.push(coffee);
	button_items.push(yes_stamp);
	button_items.push(no_stamp);
	//...more
	
	/*--------------------------------*/

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

	test->draw(win);

	//dayShowScreen->draw(win,sf::RenderStates::Default);

	win.display();
}