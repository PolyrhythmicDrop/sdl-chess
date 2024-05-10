#include "IdleGameState.h"
#include "GameStateMachine.h"
#include "InMenuGameState.h"

IdleGameState::IdleGameState()
{}

IGameState& IdleGameState::getInstance()
{
	static IdleGameState idleGameState;
	return idleGameState;
}

void IdleGameState::enter(GameStateMachine* gsm)
{
	gsm->subscribeToEventManager(EventManager::getEventManagerInstance());
}

void IdleGameState::changeState(GameStateMachine* gsm, std::string eventString)
{
	if (eventString == "Esc")
	{
		gsm->setGameState(InMenuGameState::getInstance());
	}
}

void IdleGameState::exit(GameStateMachine* gsm)
{
	gsm->unsubscribeToEventManager(EventManager::getEventManagerInstance());
}

void IdleGameState::subscribeToEventManager(EventManager & manager, GameStateMachine* gsm)
{
	manager.Subscribe(SDL_KEYUP, [this, gsm](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && gsm->getCurrentState() == this)
		{
			changeState(gsm, "Esc");
		}
		});
}

void IdleGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}