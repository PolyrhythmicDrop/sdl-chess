#pragma once
#include "GameObject.h"
#include "IDrawable.h"
#include <SDL.h>
#include <stdio.h>
#include <functional>

class Decoration : public GameObject, virtual public IDrawable
{
private:	
	

public:

	Decoration(std::string name, std::string path);

	~Decoration();	


};

