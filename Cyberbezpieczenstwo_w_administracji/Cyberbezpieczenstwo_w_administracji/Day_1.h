#pragma once
#include "Day.h"

class Day_1 : public Day
{
public:
	bool coffee_clicked;


	Day_1();
	void update(GameState &gs) override;
};