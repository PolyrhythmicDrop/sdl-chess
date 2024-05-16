#pragma once
#include "IProgramState.h"

class IdleProgramState :  public IProgramState
{
public:

	IdleProgramState();
	~IdleProgramState() {};

	static IProgramState& getInstance();

	virtual void enter(ProgramStateMachine* psm);
	virtual void changeState(ProgramStateMachine* psm, std::string eventString);
	virtual void exit(ProgramStateMachine* psm);

	virtual void subscribeToEventManager(EventManager& manager, ProgramStateMachine* psm);
	virtual void unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* psm);
};

