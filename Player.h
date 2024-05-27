#pragma once
#include <iostream>

class Player
{
public:

	Player(std::string name, int color);
	Player(const Player& player);
	Player& operator=(const Player& other);

	~Player() {};

	std::string _name;

	int _color;

};

