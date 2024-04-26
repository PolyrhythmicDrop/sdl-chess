#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
// Texture wrapper class
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

	void initTexture();

	/// <summary>
	/// Creates a surface using an image path, then creates a texture from that surface.
	/// </summary>
	/// <param name="renderer">The renderer to render the texture using</param>
	/// <param name="path">File path for the image to load</param>
	/// <returns></returns>
	bool loadTextureFromSurface(std::string path);

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

	/// <summary>
	/// Render the texture at the specified point.
	/// </summary>
	/// <param name="x">The X coordinate to render the texture</param>
	/// <param name="y">The Y coordinate to render the texture</param>
	/// <param name="clip">The rectangle to use for clip rendering, aka the srcrect for SDL_RenderCopy(). NULL by default; do not pass a clip if you want to render the whole texture.</param>
	void renderTexture(int x, int y, int w, int h, SDL_Rect clip);

	SDL_Renderer* getRenderer();

	// Get dimensions of texture
	int getTextureWidth();
	int getTextureHeight();

};

