#include "InMenuProgramState.h"
#include "InEscMenuState.h"
#include "InactiveMenuState.h"

InMenuProgramState::InMenuProgramState() {}

IProgramState& InMenuProgramState::getInstance()
{
	static InMenuProgramState inMenuGameState;
	return inMenuGameState;
}

void InMenuProgramState::enter(ProgramStateMachine* psm)
{
	psm->createEscMenu();
	psm->getEscMenu()->setMenuState(InEscMenuState::getInstance());
	subscribeToEventManager(EventManager::getEventManagerInstance(), psm);
}

void InMenuProgramState::changeState(ProgramStateMachine* psm, std::string eventString)
{
	if (eventString == "ClearMenu")
	{
		psm->setProgramState(IdleProgramState::getInstance());
	}
}

void InMenuProgramState::exit(ProgramStateMachine* psm)
{
	// psm->getEscMenu()->setMenuState(InactiveMenuState::getInstance());
	unsubscribeToEventManager(EventManager::getEventManagerInstance(), psm);
	psm->getEscMenu()->~SceneEscMenu();
	
}

void InMenuProgramState::subscribeToEventManager(EventManager& manager, ProgramStateMachine* psm)
{
	
	psm->getEscMenu()->addListener(false, [this, psm](bool active)
		{
			if (active != true)
			{
				changeState(psm, "ClearMenu");
			}
		});
	
}

void InMenuProgramState::unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* psm)
{
	manager.Unsubscribe(SDL_USEREVENT);
	psm->getEscMenu()->removeListener(false);
}