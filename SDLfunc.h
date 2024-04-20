#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDLfunc
{
		// Public members
public:
	// The SDL window
	SDL_Window* sdlWindow = NULL;

	// The renderer created for the SDL window
	SDL_Renderer* windowRenderer = NULL;

	// The SDL surface contained by the window
	SDL_Surface* windowSurface = NULL;

	// The currently displayed PNG surface
	SDL_Surface* pngSurface = NULL;

	// The currently displayed texture
	SDL_Texture* loadedTexture = NULL;

	// Constructors
	SDLfunc();

	// Methods
	
	/// <summary>
	/// Initialize SDL
	/// </summary>
	/// <returns>True if initialization was successful, false if not.</returns>
	bool Init();

	/// <summary>
	/// Initialize the SDL IMG library.
	/// </summary>
	/// <param name="flags">The flags the initialize IMG with. There can be multiple flags, OR'd together. To add more flags after running InitIMG(), call IMG_Init() with the new flags.</param>
	/// <returns></returns>
	bool InitIMG(IMG_InitFlags flags);

	/// <summary>
	/// Creates a window, which functions as the main window for the game.
	/// </summary>
	/// <param name="width">The width of the window.</param>
	/// <param name="height">The height of the window.</param>
	/// <returns></returns>
	SDL_Window* createWindow(int width, int height);

	/// <summary>
	/// Creates a renderer for a window, and also sets the draw color for that renderer.
	/// </summary>
	/// <param name="window">The window to create the renderer for.</param>
	/// <param name="flags">The renderer flags to pass.</param>
	/// <param name="r">The red channel for the draw color.</param>
	/// <param name="g">The green channel for the draw color.</param>
	/// <param name="b">The blue channel for the draw color.</param>
	/// <param name="a">The alpha channel for the draw color.</param>
	/// <returns></returns>
	SDL_Renderer* createRenderer(SDL_Window* window, SDL_RendererFlags flags, int r, int g, int b, int a);

	/// <summary>
	/// Converts an RGBA color from int to Uint8 for use in renderer creation.
	/// </summary>
	/// <param name="r">Red channel</param>
	/// <param name="g">Green channel</param>
	/// <param name="b">Blue channel</param>
	/// <param name="a">Alpha channel</param>
	/// <returns>An array of Uint8 color values</returns>
	std::array<Uint8, 4> colorConverter(int r, int g, int b, int a);

	/// <summary>
	/// Loads up a media file to be passed to a surface .
	/// </summary>
	/// <returns></returns>
	bool loadMedia();

	/// <summary>
	/// Loads media at the specified path to the surface created from the main window (sdlWindow).
	/// </summary>
	/// <param name="path">The media path</param>
	/// <returns></returns>
	SDL_Surface* loadSurface(std::string path);

	/// Closes SDL and frees resources
	void Close();
};

