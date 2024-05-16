#pragma once
#include "EventManager.h"

class ProgramStateMachine;

class IProgramState
{
public:
	virtual ~IProgramState() {};

	virtual void enter(ProgramStateMachine* gsm) = 0;
	virtual void changeState(ProgramStateMachine* gsm, std::string eventString = 0) = 0;
	virtual void exit(ProgramStateMachine* gsm) = 0;

	virtual void subscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm) = 0;
	virtual void unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm) = 0;
};

