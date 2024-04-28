#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

// Texture loader class
class Texture
{
private:

	// The actual hardware texture
	SDL_Texture* _texture;

	// Renderer to render the texture
	SDL_Renderer* _renderer;

	// Dimensions of the texture
	int _width;
	int _height;

public:
	// Constructor
	Texture(SDL_Renderer* renderer);

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

	SDL_Texture* const getTexture();

	/// <summary>
	/// Free the texture, if one exists, and re-initialize the member variables
	/// </summary>
	void freeTexture();

};

