#include "InMenuProgramState.h"
#include "InEscMenuState.h"
#include "InactiveMenuState.h"

InMenuProgramState::InMenuProgramState() {}

IProgramState& InMenuProgramState::getInstance()
{
	static InMenuProgramState inMenuGameState;
	return inMenuGameState;
}

void InMenuProgramState::enter(ProgramStateMachine* gsm)
{
	gsm->createEscMenu();
	gsm->getEscMenu()->setMenuState(InEscMenuState::getInstance());
	subscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
}

void InMenuProgramState::changeState(ProgramStateMachine* gsm, std::string eventString)
{
	if (eventString == "ClearMenu")
	{
		gsm->setProgramState(IdleProgramState::getInstance());
	}
}

void InMenuProgramState::exit(ProgramStateMachine* gsm)
{
	// gsm->getEscMenu()->setMenuState(InactiveMenuState::getInstance());
	unsubscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
	gsm->getEscMenu()->~SceneEscMenu();
	
}

void InMenuProgramState::subscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm)
{
	
	gsm->getEscMenu()->addListener(false, [this, gsm](bool active)
		{
			if (active != true)
			{
				changeState(gsm, "ClearMenu");
			}
		});
	
}

void InMenuProgramState::unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* gsm)
{
	manager.Unsubscribe(SDL_USEREVENT);
	gsm->getEscMenu()->removeListener(false);
}