#pragma once
#include "Player.h"

class HumanPlayer :  public Player
{

public:

	HumanPlayer(Player const& player, std::string name, int color);

};

