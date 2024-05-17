#include "InMenuProgramState.h"
#include "InEscMenuState.h"
#include "InactiveMenuState.h"
#include "InGameProgramState.h"
#include "easylogging++.h"

InMenuProgramState::InMenuProgramState() {}

IProgramState& InMenuProgramState::getInstance()
{
	static InMenuProgramState inMenuGameState;
	return inMenuGameState;
}

void InMenuProgramState::enter(ProgramStateMachine* psm)
{
	LOG(TRACE) << "In Menu Program State entered!";
	psm->createEscMenu();
	psm->getEscMenu()->setMenuState(InEscMenuState::getInstance());
	subscribeToEventManager(EventManager::getEventManagerInstance(), psm);
}

void InMenuProgramState::changeState(ProgramStateMachine* psm, std::string eventString)
{
	if (eventString == "ClearMenu" && psm->getPreviousState() == &IdleProgramState::getInstance())
	{
		psm->setProgramState(IdleProgramState::getInstance());
	}
	if (eventString == "ClearMenu" && psm->getPreviousState() == &InGameProgramState::getInstance())
	{
		psm->setProgramState(InGameProgramState::getInstance());
	}
}

void InMenuProgramState::exit(ProgramStateMachine* psm)
{
	LOG(TRACE) << "In Menu Program State exited!";
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