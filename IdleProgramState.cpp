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

void IdleProgramState::enter(ProgramStateMachine* psm)
{
	psm->subscribeToEventManager(EventManager::getEventManagerInstance());
}

void IdleProgramState::changeState(ProgramStateMachine* psm, std::string eventString)
{
	if (eventString == "Esc")
	{
		psm->setProgramState(InMenuProgramState::getInstance());
	}
}

void IdleProgramState::exit(ProgramStateMachine* psm)
{
	psm->unsubscribeToEventManager(EventManager::getEventManagerInstance());
}

void IdleProgramState::subscribeToEventManager(EventManager & manager, ProgramStateMachine* psm)
{
	manager.Subscribe(SDL_KEYUP, [this, psm](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && psm->getCurrentState() == this)
		{
			changeState(psm, "Esc");
		}
		});
}

void IdleProgramState::unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* psm)
{}