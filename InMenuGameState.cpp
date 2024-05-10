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
	gsm->getEscMenu()->~SceneEscMenu();
	unsubscribeToEventManager(EventManager::getEventManagerInstance(), gsm);
}

void InMenuGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	manager.Subscribe(SDL_USEREVENT, [this, gsm](SDL_Event const& event) {
		if (event.user.code == 20)
		{
			changeState(gsm, "ClearMenu");
		}
		});
}

void InMenuGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	manager.Unsubscribe(SDL_USEREVENT);
}