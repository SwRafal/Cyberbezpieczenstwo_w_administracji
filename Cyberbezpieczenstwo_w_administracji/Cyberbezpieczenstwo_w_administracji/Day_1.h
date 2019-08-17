#pragma once
#include "Day.h"

class Day_1 : public Day
{
public:
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
	bool change_login;
	bool change_password;
	bool remember_password;
	bool write_down_password;
	bool login_wifi;
	//Quest 4
	bool click_email;
	bool refused_email;

	Day_1();
	void update(GameState &gs) override;
};