#include "Player.h"
#include "easylogging++.h"

Player::Player(std::string name, int color) :
	_name(name),
	_color(color),
	_check(false)
{}

Player::Player(const Player& player)
{
	_name = player._name;
	_color = player._color;
	_check = player._check;
}

Player& Player::operator=(const Player& other)
{
	LOG(TRACE) << "Assignment operator called!";
	return *this;
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