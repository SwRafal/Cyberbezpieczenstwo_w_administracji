#pragma once

class GameState;

class Day
{
public:
	virtual void update(GameState *gs) = 0;
};