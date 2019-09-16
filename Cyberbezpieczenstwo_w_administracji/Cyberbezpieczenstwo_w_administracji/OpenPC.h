#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include "textBubble.h"
#include "email.h"

#define PC_OPENED_POS_X 200
#define PC_OPENED_POS_Y 60
#define PC_OPENED_WIDTH 800
#define PC_OPENED_HEIGHT 600

#define EXIT_SIZE 50

#define USER_WIDTH 300
#define USER_HEIGHT 50
#define USER_CHARSIZE 24

#define WIFIS_SIZE 200
#define WIFIS_POS_X 300
#define WIFIS_POS_Y 250

#define ACCOUNT_SIZE 200
#define ACCOUNT_POS_X 700
#define ACCOUNT_POS_Y 250

#define WIFI_POS_X 250
#define WIFI_POS_Y 110
#define WIFI_WIDTH 400
#define WIFI_HEIGHT 50
#define WIFI_CHARSIZE 22

#define LINE_WIDTH 400
#define LINE_HEIGHT 50
#define LOGIN_POS_X 400
#define LOGIN_POS_Y 300
#define PASSWORD_POS_X 400
#define PASSWORD_POS_Y 400
#define LINE_CHARSIZE 24

#define OK_SIZE 50
#define OK_POS_X 900
#define OK_POS_Y 560
#define OK_CHARSIZE 20

#define INFO_DELAY 3000

#define SCREEN_FRAME_POS_X 177
#define SCREEN_FRAME_POS_Y 17



class OpenPC : public sf::Sprite
{
public:
	enum PC_STATE
	{
		USERS = 0,
		DESKTOP,
		SET_PASSWORD,
		LOGIN_WIFI,
		OUTLOOK,
		MAIL,
		LOGIN,
		DESKTOP_KRYSIA,
		INFO_DISPLAY
	};

	bool internet_works = false;

	gm::Information *communique = nullptr;
	bool show_communique = false;

	void newMail(sf::String title,sf::String sender,sf::String content);
	void setMailButtonActive();
	void setMailButtonInactive();

	void setExitButtonActive();
	void setExitButtonInactive();
	

private:
	//Rzeczy w komputerze
	PC_STATE state;
	PC_STATE previousState;
	gm::Button *exit = nullptr;

	gm::TextButton *user_marek = nullptr;
	gm::TextButton *user_krysia = nullptr;
	gm::TextButton *user_player = nullptr;

	gm::Button *wifis = nullptr;
	gm::Button *account_manager = nullptr;
		//Account manager
	gm::TextField *login = nullptr;
	gm::TextField *password = nullptr;
		//Wifis
	gm::TextButton *wifi_mindswszelakich = nullptr;
	gm::TextButton *wifi_mindswszelakich_gov = nullptr;
	gm::TextButton *wifi_mindswszelakich_p1 = nullptr;
	gm::TextButton *wifi_Xfon_zosi = nullptr;
	gm::TextButton *wifi_stolowka_wiesi = nullptr;
	
	gm::TextButton *ok = nullptr;

	bool exitButtonActive;

	//frame

	Sprite screenFrame;
	
	//email
	mail email;

	textBubble *info = nullptr;
	sf::Int32 info_time;

	//krysia desktop
	sf::Sprite krysia_folders;

	//info
	sf::Sprite info_display;
	
public:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	OpenPC(sf::Texture *texture, sf::Font *font);
	~OpenPC();

	void draw(sf::RenderWindow &win);
	bool update(sf::RenderWindow &win); //GameState can know if book should be closed

	void setState(PC_STATE state);
	PC_STATE getState() { return state; }

	void setLogin(sf::String login);
	void setPassword(sf::String password);
	sf::String getLogin() { return login->getTextString(); }
	sf::String getPassword() { return password->getTextString(); }


	//bools
	bool krysiaPasswordKnown;
	bool showExcessUsers;

	sf::Sprite kurierexpol;
	sf::Sprite* bonusInfo;
	bool newInfo = false;
};