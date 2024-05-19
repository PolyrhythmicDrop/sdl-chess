#include "Player.h"
#include "easylogging++.h"

Player::Player(std::string name, char color) :
	_name(name),
	_color(color)
{}

Player::Player(const Player& player)
{
	_name = player._name;
	_color = player._color;
}

Player& Player::operator=(const Player& other)
{
	LOG(TRACE) << "Assignment operator called!";
	return *this;
}