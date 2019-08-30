#include "OpenPC.h"

OpenPC::OpenPC(sf::Texture *texture, sf::Font *font)
{
	this->setTexture(*texture);
	this->setPosition(PC_OPENED_POS_X, PC_OPENED_POS_Y);
	state = USERS;

	gm::Assets::LoadTexture("EXIT_BUTTON", TEXTURE_EXIT_BUTTON);
	if (gm::Assets::getTexture("EXIT_BUTTON") == nullptr)
		error_win_close();
	else
	{
		exit = new gm::Button;
		exit->setSize(EXIT_SIZE, EXIT_SIZE);
		exit->setPosition(sf::Vector2f(PC_OPENED_POS_X + PC_OPENED_WIDTH - EXIT_SIZE, PC_OPENED_POS_Y));
		exit->setTexture(gm::Assets::getTexture("EXIT_BUTTON"));
	}

	/*USERS*/
	user_marek = new gm::TextButton(*gm::Assets::getFont());
	user_marek->setSize(sf::Vector2f(USER_WIDTH, USER_HEIGHT));
	user_marek->setPosition(sf::Vector2f(SCREEN_WIDTH/2 - USER_WIDTH/2, 200));
	user_marek->setTextString("Marek");
	user_marek->setTextSize(USER_CHARSIZE);
	user_krysia = new gm::TextButton(*gm::Assets::getFont());
	user_krysia->setSize(sf::Vector2f(USER_WIDTH, USER_HEIGHT));
	user_krysia->setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - USER_WIDTH / 2, 300));
	user_krysia->setTextString("Krysia");
	user_krysia->setTextSize(USER_CHARSIZE);
	user_player = new gm::TextButton(*gm::Assets::getFont());
	user_player->setSize(sf::Vector2f(USER_WIDTH, USER_HEIGHT));
	user_player->setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - USER_WIDTH / 2, 400));
	user_player->setTextString("Admin");//Login i has³o z gamedata!!!!
	user_player->setTextSize(USER_CHARSIZE);

	/*DESKTOP*/
	gm::Assets::LoadTexture("WIFI_BUTTON", TEXTURE_WIFI_BUTTON);
	if (gm::Assets::getTexture("WIFI_BUTTON") == nullptr)
		error_win_close();
	else
	{
		wifis = new gm::Button(sf::Vector2f(WIFIS_POS_X, WIFIS_POS_Y), sf::Vector2f(WIFIS_SIZE, WIFIS_SIZE));
		wifis->setTexture(gm::Assets::getTexture("WIFI_BUTTON"));
	}

	gm::Assets::LoadTexture("ACCOUNT_BUTTON", TEXTURE_ACCOUNT_BUTTON);
	if (gm::Assets::getTexture("ACCOUNT_BUTTON") == nullptr)
		error_win_close();
	else
	{
		account_manager = new gm::Button(sf::Vector2f(ACCOUNT_POS_X, ACCOUNT_POS_Y), sf::Vector2f(ACCOUNT_SIZE, ACCOUNT_SIZE));
		account_manager->setTexture(gm::Assets::getTexture("ACCOUNT_BUTTON"));
	}

	/*WIFI*/
	wifi_mindswszelakich = new gm::TextButton(*gm::Assets::getFont());
	wifi_mindswszelakich->setSize(sf::Vector2f(WIFI_WIDTH, WIFI_HEIGHT));
	wifi_mindswszelakich->setPosition(sf::Vector2f(WIFI_POS_X,WIFI_POS_Y));
	wifi_mindswszelakich->setTextString(L"Mindswszelakich");
	wifi_mindswszelakich->setTextSize(WIFI_CHARSIZE);

	wifi_mindswszelakich_gov = new gm::TextButton(*gm::Assets::getFont());
	wifi_mindswszelakich_gov->setSize(sf::Vector2f(WIFI_WIDTH, WIFI_HEIGHT));
	wifi_mindswszelakich_gov->setPosition(sf::Vector2f(WIFI_POS_X, WIFI_POS_Y+100));
	wifi_mindswszelakich_gov->setTextString(L"Mindswszelakich.gov");
	wifi_mindswszelakich_gov->setTextSize(WIFI_CHARSIZE);

	wifi_mindswszelakich_p1 = new gm::TextButton(*gm::Assets::getFont());
	wifi_mindswszelakich_p1->setSize(sf::Vector2f(WIFI_WIDTH, WIFI_HEIGHT));
	wifi_mindswszelakich_p1->setPosition(sf::Vector2f(WIFI_POS_X, WIFI_POS_Y + 200));
	wifi_mindswszelakich_p1->setTextString(L"Mindswszelakich piêtro 1");
	wifi_mindswszelakich_p1->setTextSize(WIFI_CHARSIZE);

	wifi_Xfon_zosi = new gm::TextButton(*gm::Assets::getFont());
	wifi_Xfon_zosi->setSize(sf::Vector2f(WIFI_WIDTH, WIFI_HEIGHT));
	wifi_Xfon_zosi->setPosition(sf::Vector2f(WIFI_POS_X, WIFI_POS_Y + 300));
	wifi_Xfon_zosi->setTextString(L"Xfo³nZosi(Zabezpieczona)");
	wifi_Xfon_zosi->setTextSize(WIFI_CHARSIZE);

	wifi_stolowka_wiesi = new gm::TextButton(*gm::Assets::getFont());
	wifi_stolowka_wiesi->setSize(sf::Vector2f(WIFI_WIDTH, WIFI_HEIGHT));
	wifi_stolowka_wiesi->setPosition(sf::Vector2f(WIFI_POS_X, WIFI_POS_Y + 400));
	wifi_stolowka_wiesi->setTextString(L"Wi-fi sto³ówka Wiesi");
	wifi_stolowka_wiesi->setTextSize(WIFI_CHARSIZE);

	/*Account_manager*/
	login = new gm::TextField(*gm::Assets::getFont());
	login->setSize(sf::Vector2f(LINE_WIDTH, LINE_HEIGHT));
	login->setPosition(sf::Vector2f(LOGIN_POS_X, LOGIN_POS_Y));
	login->setTextSize(LINE_CHARSIZE);
	login->setTextString("Admin");///GAMEDATA !!!!!
	password = new gm::TextField(*gm::Assets::getFont());
	password->setSize(sf::Vector2f(LINE_WIDTH, LINE_HEIGHT));
	password->setPosition(sf::Vector2f(PASSWORD_POS_X, PASSWORD_POS_Y));
	password->setTextSize(LINE_CHARSIZE);
	password->setTextString("Admin");//GAMEDATA!!!!!!!

	ok = new gm::TextButton(*gm::Assets::getFont());
	ok->setSize(OK_SIZE, OK_SIZE);
	ok->setPosition(OK_POS_X, OK_POS_Y);
	ok->setTextSize(OK_CHARSIZE);
	ok->setTextString("OK");

	gm::Assets::LoadTexture("THOUGHT_BUBBLE", TEXTURE_TEXT_BUBBLE);
	if (gm::Assets::getTexture("THOUGHT_BUBBLE") == nullptr)
		error_win_close();
	else
	{
		info = new textBubble(gm::Assets::getTexture("THOUGHT_BUBBLE"));
		info->setBubblePosition(0, -300);
	}	
}
OpenPC::~OpenPC()
{
	gm::Assets::EraseTexture("ACCOUNT_BUTTON");
	gm::Assets::EraseTexture("WIFI_BUTTON");
	gm::Assets::EraseTexture("EXIT_BUTTON");

	delete exit;
	exit = nullptr;

	delete user_marek;
	user_marek = nullptr;
	delete user_krysia;
	user_krysia = nullptr;
	delete user_player;
	user_player = nullptr;

	delete wifis;
	wifis = nullptr;
	delete account_manager;
	account_manager = nullptr;

	delete wifi_mindswszelakich;
	wifi_mindswszelakich = nullptr;
	delete wifi_mindswszelakich_gov;
	wifi_mindswszelakich_gov = nullptr;
	delete wifi_mindswszelakich_p1;
	wifi_mindswszelakich_p1 = nullptr;
	delete wifi_Xfon_zosi;
	wifi_Xfon_zosi = nullptr;
	delete wifi_stolowka_wiesi;
	wifi_stolowka_wiesi = nullptr;

	delete login;
	login = nullptr;
	delete password;
	password = nullptr;
	delete ok;
	ok = nullptr;

	delete info;
	info = nullptr;
}

void OpenPC::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);

	switch (state)
	{
	case USERS:
		win.draw(*user_marek);
		win.draw(*user_krysia);
		win.draw(*user_player);
		break;
	case DESKTOP:
		win.draw(*wifis);
		win.draw(*account_manager);
		break;
	case LOGIN_WIFI:
		win.draw(*wifi_mindswszelakich);
		win.draw(*wifi_mindswszelakich_gov);
		win.draw(*wifi_mindswszelakich_p1);
		win.draw(*wifi_Xfon_zosi);
		win.draw(*wifi_stolowka_wiesi);
		win.draw(*ok);
		break;
	case SET_PASSWORD:
		win.draw(*login);
		win.draw(*password);
		win.draw(*ok);
		break;
	default:
		break;
	}

	info->draw(win);

	win.draw(*exit);
}

bool OpenPC::update(sf::RenderWindow &win)
{
	if (exit->clicked(win))
		return true;

	switch (state)
	{
	case USERS:
		if (user_marek->clicked(win))
		{
			info->changeText(L"Nie znam has³a do tego konta...");
			info->setBubblePosition(400, 100);
			info->showBubble();
			info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + INFO_DELAY;
		}
		else if (user_krysia->clicked(win))
		{
			info->changeText(L"Nie znam has³a do tego konta...");
			info->setBubblePosition(400, 100);
			info->showBubble();
			info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + INFO_DELAY;
		}
		else if (user_player->clicked(win))
			setState(DESKTOP);
		break;
	case DESKTOP:
		if (wifis->clicked(win))
			setState(LOGIN_WIFI);
		else if (account_manager->clicked(win))
			setState(SET_PASSWORD);
		break;
	case LOGIN_WIFI:
		if (wifi_mindswszelakich->clicked(win) || wifi_mindswszelakich_gov->clicked(win) || wifi_mindswszelakich_p1->clicked(win));
		//certyfikat
		else if (wifi_Xfon_zosi->clicked(win))
		{
			info->changeText(L"Nie znam has³a do tej sieci...");
			info->setBubblePosition(400, 100);
			info->showBubble();
			info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + INFO_DELAY;
		}
		else if (wifi_stolowka_wiesi->clicked(win))
		{
			info->changeText(L"Nie powinienem siê pod³¹czaæ do sieci publicznych...");
			info->setBubblePosition(400, 100);
			info->showBubble();
			info_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + INFO_DELAY;
		}
		else if (ok->clicked(win))
			setState(DESKTOP);
		break;
	case SET_PASSWORD:
		login->update(win, gm::Core::getEnteredChar());
		password->update(win, gm::Core::getEnteredChar());
		if (ok->clicked(win))
		{
			setState(DESKTOP);
		}
		break;
	default:
		break;
	}

	info->animate();
	if (info_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		info->closeBubble();

	return false;
}

void OpenPC::setState(PC_STATE state)
{
	this->state = state;
}

void OpenPC::setLogin(sf::String login)
{
	this->login->setTextString(login);
}

void OpenPC::setPassword(sf::String password)
{
	this->password->setTextString(password);
}