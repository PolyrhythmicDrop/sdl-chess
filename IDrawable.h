#pragma once
#include "SDLfunc.h"

/// <summary>
/// "Interface" for drawable game objects.
/// </summary>
class IDrawable
{
public:

	bool _draw;

	IDrawable();

	virtual ~IDrawable() {};

	virtual void loadTexture() = 0;
	virtual void setDrawDimByObjDim(SDL_Rect dim);
	virtual SDL_Texture*& getCurrentTexture();

	const SDL_Rect& getDrawDimensions();
	void setDrawDimensions(int x, int y, int w, int h);
	void setDrawPosition(int x, int y);

	void setDrawScale(int w, int h);
	void setDrawScaleByTexture();

	const int& getZ() const;
	void setZ(int z);


protected:

	SDL_Rect _drawDimensions;

	// Z-index for drawing purposes. Higher values render on top of lower values.
	int _zIndex;

	SDL_Texture* _currentTexture;
	
};

