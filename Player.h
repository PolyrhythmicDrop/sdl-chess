#pragma once
#include <iostream>

class Player
{
public:

	Player(std::string name, char color);
	Player(const Player& player);
	Player& operator=(const Player& other);

	~Player() {};

	std::string _name;

	char _color;

};

