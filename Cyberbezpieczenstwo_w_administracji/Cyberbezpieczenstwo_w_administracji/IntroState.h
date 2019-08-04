#pragma once

#include "Engine/Engine.h"
#include "Game.h"

class IntroState : public gm::SlideFrame
{
	private:
	gm::gameDataRef data;

public:
	IntroState();
	~IntroState();
};
