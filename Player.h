#pragma once
#include <iostream>

class Player
{

private:

	std::string _name;

	int _color;

	// is this player currently in check?
	bool _check = false;

public:

	Player(std::string name, int color);
	Player(const Player& player);
	Player& operator=(const Player& other);

	~Player() {};

	std::string getName();
	void setName(std::string name);

	int getColor();
	void setColor(int color);

	bool getCheck();
	void setCheck(bool check);


};

