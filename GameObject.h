#pragma once

// Pure abstract class for game objects
class GameObject
{
public:

	/// <summary>
	/// Assigns a texture to an object.
	/// </summary>
	virtual void assignTexture();

	virtual void draw();
};

