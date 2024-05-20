#pragma once
#include "EventManager.h"

class ProgramStateMachine;

class IProgramState
{
public:
	virtual ~IProgramState() {};

	virtual void enter(ProgramStateMachine* psm) = 0;
	virtual void changeState(ProgramStateMachine* psm, std::string eventString = 0) = 0;
	virtual void exit(ProgramStateMachine* psm) = 0;

	virtual void subscribeToEventManager(EventManager& manager, ProgramStateMachine* psm) = 0;
	virtual void unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* psm) = 0;
};

