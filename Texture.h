#pragma once
#include "ServiceLocator.h"

// Texture loader class
class Texture
{
private:

	// The actual hardware texture
	SDL_Texture* _loadedTexture;

public:
	// Constructor
	Texture();

	// Deep copy constructor, for copying textures
	Texture(const Texture& texture);

	// Assignment operator
	Texture& operator=(const Texture& other);

	/// <summary>
	/// Removes the class from memory and deallocates the texture. Runs Texture::freeTexture().
	/// </summary>
	~Texture();

	/// <summary>
	/// Loads a texture from an image, without having to create a surface.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="path"></param>
	/// <returns></returns>
	SDL_Texture* loadTextureFromImage(std::string path);

	SDL_Texture* getTexture();

	/// <summary>
	/// Free the texture, if one exists, and re-initialize the member variables
	/// </summary>
	void freeTexture();

};

