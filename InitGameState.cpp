#include "InitGameState.h"
#include "easylogging++.h"
#include "GameScene.h"

InitGameState::InitGameState() {};

void InitGameState::enter(GameStateMachine* gsm)
{
	// ** Player Initialization ** //
	std::string p1Name, p2Name;
	std::cout << "Player One, enter your name:\n";
	std::cin >> p1Name;
	std::cout << "Player Two, enter your name:\n";
	std::cin >> p2Name;
	// TODO: Let the players select their color. For now, hard-coding who goes first.
	gsm->getGameScene()->setPlayerOne(p1Name, 'w');
	gsm->getGameScene()->setPlayerTwo(p2Name, 'b');

	// ** Chessboard Initialization ** //
	// Build the chessboard squares and add the board grid to the render queue
	LOG(TRACE) << "Initialize Game State entered!";
	gsm->getGameScene()->getBoard()->buildChessboard();
	LOG(TRACE) << "Chessboard squares and position constructed!";
	gsm->getGameScene()->getBoard()->addBoardToRender();
	LOG(TRACE) << "Chessboard added to render queue!";
	// Add the current square positions to the debug log
	gsm->getGameScene()->getBoard()->printSquarePositions();
	// ** End Chessboard Initialization ** //

	// ** Initial Piece Placement ** //
	gsm->getGameScene()->getManager()->setUpGame();

}

void InitGameState::changeState(GameStateMachine* gsm)
{}

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
