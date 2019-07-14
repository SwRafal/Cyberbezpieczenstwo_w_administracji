#pragma once

#include <memory>
#include <stack>

#include "SlideFrame.h"

namespace gm
{
	typedef std::unique_ptr<SlideFrame> StateRef;

	class StateMachine
	{

	public:
		StateMachine() {};
		~StateMachine() {};

		void addState(StateRef newState, bool isReplacing = true);
		void removeState();

		void processStateChanges();

		StateRef& getActiveState();
	
	private:
		std::stack<StateRef> states;
		StateRef newState;

		bool isRemoving;
		bool isAdding;
		bool isReplacing;
	};
}