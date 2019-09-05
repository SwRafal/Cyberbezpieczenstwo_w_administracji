#pragma once
#include "Day.h"
#include "textBubble.h"
#include "OfficeApplicant.h"

#define THOUGHT_TIME 3000


class Day_1 : public Day
{
public:
	int state;
	bool init;

	bool showButtons;

	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	OfficeApplicant *ITguy = nullptr;

	//Quest 1
	bool coffee_clicked;
	bool open_book;
	bool close_book;
	//Quest 2
	bool click_telephone;
	bool finish_telephone;
	bool finish_thought;
	bool choose_user;
	bool log_in;
	bool finish_dialog;
	bool click_mobile;
	bool put_mobile;
	bool change_lines;
	bool remember_password;
	bool write_down_password;
	bool login_wifi;
	bool choose_wifi;
	bool refuse_wifi;
	bool phone_it;
	bool finish_phone_it;
	bool rj45;
	//Quest 4
	bool click_email;
	bool refused_email;

	Day_1();
	~Day_1();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};