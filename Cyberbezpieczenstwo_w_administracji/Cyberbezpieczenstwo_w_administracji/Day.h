#pragma once
#include "Engine/Core.h"

class GameState;

class Day
{
public:
	virtual void update(GameState *gs) = 0;
};