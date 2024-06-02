#include "Player.h"
#include "StockfishPlayer.h"
#include "HumanPlayer.h"
#include "easylogging++.h"

Player::Player(std::string name, int color, PlayerType type) :
	_name(name),
	_color(color),
	_check(false),
	_playerType(type)
{
	if (_playerType == HUMAN)
	{
		createHumanPlayer();
	}
	else if (_playerType == STOCKFISH)
	{
		createStockfishPlayer();
	}
}

Player::Player(const Player& player)
{
	_name = player._name;
	_color = player._color;
	_check = player._check;
	_playerType = player._playerType;
}

Player& Player::operator=(const Player& other)
{
	LOG(TRACE) << "Assignment operator called!";
	return *this;
}

HumanPlayer Player::createHumanPlayer()
{
	_playerType = HUMAN;
	HumanPlayer humanPlayer(*this, _name, _color);
	return humanPlayer;
}

StockfishPlayer Player::createStockfishPlayer()
{
	_playerType = STOCKFISH;
	StockfishPlayer fishPlayer(*this, _name, _color);
	return fishPlayer;
}

std::string Player::getName()
{
	return _name;
}

void Player::setName(std::string name)
{
	_name = name;
}

int Player::getColor()
{
	return _color;
}

void Player::setColor(int color)
{
	_color = color;
}

bool Player::getCheck()
{
	return _check;
}

void Player::setCheck(bool check)
{
	_check = check;
}