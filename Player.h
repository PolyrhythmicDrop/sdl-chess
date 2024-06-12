#pragma once
#include <iostream>

class HumanPlayer;
class StockfishPlayer;

class Player
{

public:

	enum PlayerType {
		HUMAN,
		STOCKFISH
	};

	Player(std::string name, int color, PlayerType type = PlayerType::HUMAN);
	Player(const Player& player);
	Player& operator=(const Player& other);

	virtual ~Player() {};

	HumanPlayer createHumanPlayer();
	StockfishPlayer createStockfishPlayer();

	std::string getName();
	void setName(std::string name);

	int getColor();
	void setColor(int color);

	PlayerType getPlayerType();

	bool getCheck();
	void setCheck(bool check);

private:

	std::string _name;

	int _color;

	// is this player currently in check?
	bool _check = false;

	PlayerType _playerType;

};

