#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Renderer.h"

// Texture loader class
class Texture
{
private:

	// The actual hardware texture
	SDL_Texture* _sdlTexture;

	// Renderer to render the texture
	Renderer* &_renderer;

public:
	// Constructor
	Texture(Renderer* renderer);

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

