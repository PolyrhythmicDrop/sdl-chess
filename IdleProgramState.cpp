#include "IdleProgramState.h"
#include "ProgramStateMachine.h"
#include "InMenuProgramState.h"
#include "InGameProgramState.h"
#include "easylogging++.h"

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
	LOG(TRACE) << "Idle Program State entered!";
}

void IdleProgramState::changeState(ProgramStateMachine* psm, std::string eventString)
{
	if (eventString == "Esc")
	{
		psm->setProgramState(InMenuProgramState::getInstance());
	}
	if (eventString == "StartGame")
	{
		psm->setProgramState(InGameProgramState::getInstance());
	}
}

void IdleProgramState::exit(ProgramStateMachine* psm)
{
	psm->unsubscribeToEventManager(EventManager::getEventManagerInstance());
	LOG(TRACE) << "Idle Program State exited!";
}

void IdleProgramState::subscribeToEventManager(EventManager & manager, ProgramStateMachine* psm)
{
	manager.Subscribe(SDL_KEYUP, [this, psm](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && psm->getCurrentState() == this)
		{
			changeState(psm, "Esc");
		}
		else if (event.key.keysym.sym == SDLK_RETURN && psm->getCurrentState() == this)
		{
			changeState(psm, "StartGame");
		}
		});
}

void IdleProgramState::unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* psm)
{
	manager.Unsubscribe(SDL_KEYUP);
}