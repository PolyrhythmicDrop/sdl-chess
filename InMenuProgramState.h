#pragma once
#include "IProgramState.h"
#include "ProgramStateMachine.h"

class InMenuProgramState :  public IProgramState
{
public:

	InMenuProgramState();
	~InMenuProgramState() {};

	static IProgramState& getInstance();

	virtual void enter(ProgramStateMachine* gsm);
	virtual void changeState(ProgramStateMachine* gsm, std::string eventString);
	virtual void exit(ProgramStateMachine* gsm);

	virtual void subscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm);
	virtual void unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm);
};

