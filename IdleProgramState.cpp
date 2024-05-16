#include "IdleProgramState.h"
#include "ProgramStateMachine.h"
#include "InMenuProgramState.h"

IdleProgramState::IdleProgramState()
{}

IProgramState& IdleProgramState::getInstance()
{
	static IdleProgramState idleGameState;
	return idleGameState;
}

void IdleProgramState::enter(ProgramStateMachine* gsm)
{
	gsm->subscribeToEventManager(EventManager::getEventManagerInstance());
}

void IdleProgramState::changeState(ProgramStateMachine* gsm, std::string eventString)
{
	if (eventString == "Esc")
	{
		gsm->setProgramState(InMenuProgramState::getInstance());
	}
}

void IdleProgramState::exit(ProgramStateMachine* gsm)
{
	gsm->unsubscribeToEventManager(EventManager::getEventManagerInstance());
}

void IdleProgramState::subscribeToEventManager(EventManager & manager, ProgramStateMachine* gsm)
{
	manager.Subscribe(SDL_KEYUP, [this, gsm](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && gsm->getCurrentState() == this)
		{
			changeState(gsm, "Esc");
		}
		});
}

void IdleProgramState::unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm)
{}