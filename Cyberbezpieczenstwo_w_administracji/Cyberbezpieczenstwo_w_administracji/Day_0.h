#pragma once
#include "Day.h"


class Day_0 : public Day
{
public:


	int state;
	bool showTextField;
	Day_0();
	void update(GameState* gs) override;
};