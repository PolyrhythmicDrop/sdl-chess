#pragma once

/// <summary>
/// "Interface" for drawable game objects.
/// </summary>
class IDrawable
{
public:
	void virtual assignTexture() = 0;
	void virtual draw() = 0;
};

