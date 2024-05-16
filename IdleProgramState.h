#pragma once
#include "IProgramState.h"

class IdleProgramState :  public IProgramState
{
public:

	IdleProgramState();
	~IdleProgramState() {};

	static IProgramState& getInstance();

	virtual void enter(ProgramStateMachine* gsm);
	virtual void changeState(ProgramStateMachine* gsm, std::string eventString);
	virtual void exit(ProgramStateMachine* gsm);

	virtual void subscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm);
	virtual void unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm);
};

