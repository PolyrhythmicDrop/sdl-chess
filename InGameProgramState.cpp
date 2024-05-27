#include "InGameProgramState.h"

#include "ProgramStateMachine.h"

#include "easylogging++.h"

#include "GameScene.h"
#include "IdleGameState.h"
#include "InitGameState.h"
#include "InMenuProgramState.h"
#include <memory>

InGameProgramState::InGameProgramState()
{}

IProgramState& InGameProgramState::getInstance()
{
	static InGameProgramState inGameProgramState;
	return inGameProgramState;
}

void InGameProgramState::enter(ProgramStateMachine* psm)
{
	this->subscribeToEventManager(EventManager::getEventManagerInstance(), psm);
	if (!GameScene::_instantiated)
	{
		psm->createGameScene();
		psm->getGameScene()->getManager()->setGameState(InitGameState::getInstance());
	}
	else
	{
		if (psm->getGameScene()->getManager()->_currentState != &IdleGameState::getInstance())
		{
			psm->getGameScene()->getManager()->setGameState(IdleGameState::getInstance());
		}
	}
	LOG(TRACE) << "In Game Program State entered!";
}

void InGameProgramState::changeState(ProgramStateMachine* psm, std::string eventString)
{
	if (eventString == "Esc")
	{
		psm->setProgramState(InMenuProgramState::getInstance());
	}

}

void InGameProgramState::exit(ProgramStateMachine* psm)
{
	this->unsubscribeToEventManager(EventManager::getEventManagerInstance(), psm);
	LOG(TRACE) << "In Game Program State exited!";
}

void InGameProgramState::subscribeToEventManager(EventManager& manager, ProgramStateMachine* psm)
{
	manager.Subscribe(SDL_KEYUP, [this, psm](SDL_Event const& event) {
		if (event.key.keysym.sym == SDLK_ESCAPE && psm->getCurrentState() == this)
		{
			changeState(psm, "Esc");
		}
		});
}

void InGameProgramState::unsubscribeToEventManager(EventManager& manager, ProgramStateMachine* psm)
{
	manager.Unsubscribe(SDL_KEYUP);
}