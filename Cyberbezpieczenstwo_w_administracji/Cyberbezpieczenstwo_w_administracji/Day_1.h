#pragma once
#include "GameState.h"

class Day_1
{
	//Quests for day_1
public:
	bool coffee_clicked;
	bool book_opened;
	bool book_closed;
	bool telephone_clicked;
	bool telephone_heard;
	bool thought_bubble_closed;
	bool logged_in;
	bool finished_dialog;
	bool mobile_clicked;
	bool mobile_put;
	bool changed_login;
	bool changed_password;//Mini-game
	bool remember_password;
	bool write_down_password;
	bool login_wifi;

	Day_1();
	void update(GameState &gs);
};