#include "InGameProgramState.h"

#include "ProgramStateMachine.h"

InGameProgramState::InGameProgramState()
{}

IProgramState& InGameProgramState::getInstance()
{
	static IdleProgramState idleGameState;
	return idleGameState;
}

void InGameProgramState::enter(ProgramStateMachine* psm)
{
	
}

void InGameProgramState::changeState(ProgramStateMachine* psm, std::string eventString)
{

}

void InGameProgramState::exit(ProgramStateMachine* psm)
{
	
}

void InGameProgramState::subscribeToEventManager(EventManager& manager, ProgramStateMachine* psm)
{
	
}

void InGameProgramState::unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* psm)
{}