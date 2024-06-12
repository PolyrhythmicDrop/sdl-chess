#pragma once
#include "SDLfunc.h"

/// <summary>
/// "Interface" for drawable game objects.
/// </summary>
class IDrawable
{
protected:

	SDL_Rect _drawDimensions;
	int _zIndex;
	SDL_Texture* _currentTexture;

public:

	bool _draw;

	IDrawable();

	virtual ~IDrawable() {};

	virtual void loadTexture() = 0;
	virtual SDL_Texture*& getCurrentTexture();

	const SDL_Rect& getDrawDimensions();
	void setDrawDimensions(int x, int y, int w, int h);
	void setDrawPosition(int x, int y);
	void setDrawScale(int w, int h);
	void setDrawScaleByTexture();

	const int& getZ();
	void setZ(int z);

	
};

