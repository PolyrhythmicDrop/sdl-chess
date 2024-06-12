#pragma once
#include "Player.h"
#include <memory>

class StockfishPlayer :  public Player
{
private:

public:

	StockfishPlayer(Player const& player, std::string name, int color);

};

