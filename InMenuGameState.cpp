#include "InMenuGameState.h"
#include "InEscMenuState.h"
#include "InactiveMenuState.h"

InMenuGameState::InMenuGameState() {}

IGameState& InMenuGameState::getInstance()
{
	static InMenuGameState inMenuGameState;
	return inMenuGameState;
}

void InMenuGameState::enter(GameStateMachine* gsm)
{
	gsm->createEscMenu();
	gsm->getEscMenu()->setMenuState(InEscMenuState::getInstance());
	subscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
}

void InMenuGameState::changeState(GameStateMachine* gsm, std::string eventString)
{
	if (eventString == "ClearMenu")
	{
		gsm->setGameState(IdleGameState::getInstance());
	}
}

void InMenuGameState::exit(GameStateMachine* gsm)
{
	// gsm->getEscMenu()->setMenuState(InactiveMenuState::getInstance());
	unsubscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
	gsm->getEscMenu()->~SceneEscMenu();
	
}

void InMenuGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	
	gsm->getEscMenu()->addListener(false, [this, gsm](bool active)
		{
			if (active != true)
			{
				changeState(gsm, "ClearMenu");
			}
		});
	
}

void InMenuGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	manager.Unsubscribe(SDL_USEREVENT);
	gsm->getEscMenu()->removeListener(false);
}