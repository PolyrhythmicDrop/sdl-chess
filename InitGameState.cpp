#include "InitGameState.h"
#include "easylogging++.h"
#include "GameScene.h"
#include "TurnWhiteGameState.h"
#include "TurnBlackGameState.h"

InitGameState::InitGameState() {};

void InitGameState::enter(GameStateMachine* gsm)
{
	LOG(TRACE) << "Initialize Game State entered!";
	// Call the Game Manager to initialize the game
	gsm->getGameManager()->setUpGame();

	changeState(gsm);
}

void InitGameState::changeState(GameStateMachine* gsm, std::string eventString)
{
	if (gsm->getGameManager()->getTurn() == 0)
	{
		gsm->setGameState(gsm->getGameManager(), TurnBlackGameState::getInstance());
	}
	else if (gsm->getGameManager()->getTurn() == 1)
	{
		gsm->setGameState(gsm->getGameManager(), TurnWhiteGameState::getInstance());
	}
}

void InitGameState::exit(GameStateMachine* gsm)
{
	LOG(TRACE) << "Initialize Game State exited!";
}

IGameState& InitGameState::getInstance()
{
	static InitGameState initState;
	return initState;
}

void InitGameState::subscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{
	
}

void InitGameState::unsubscribeToEventManager(EventManager& manager, GameStateMachine* gsm)
{}
