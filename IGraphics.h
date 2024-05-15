#pragma once
#include "GameContext.h"
#include "Renderer.h"
#include <map>

// Pure abstract class for graphics handling, should be inherited by both the NullGraphicsService and the GraphicsService.
class IGraphics
{	

public:
	// Layer for the object to be rendered in.
	enum Layer {
		BG,
		BOARD,
		PIECES,
		UI,
		MENU
	};

	~IGraphics() {};

	/// <summary>
	/// Returns the window wrapper class.
	/// </summary>
	/// <returns></returns>
	virtual Window* getWindow() = 0;

	virtual Renderer* getRenderer() = 0;

	/// <summary>
	/// Adds objects and textures to the render map. If objects are already in render map, they won't get added.
	/// </summary>
	/// <param name="layer">The render layer to add the objects to. Refer to IGraphics:Layer for possible options.</param>
	/// <param name="pairs">Vector containing all the objects and textures to add to the render map. Works best when using a scene map.</param>
	virtual void addToRenderMap(int layer, std::vector<std::pair<GameObject*, SDL_Texture*>> pairs) = 0;

	/// <summary>
	/// Removes objects and textures from the render map. Searches for supplied objects in the render map, and if it finds them, removes them.
	/// </summary>
	/// <param name="objects">The objects to remove from the render map.</param>
	virtual void removeFromRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects) = 0;

	/// <summary>
	/// Finds objects in the render map.
	/// </summary>
	/// <param name="objects">The object/texture pairs to search for.</param>
	/// <returns>A vector containing all the objects that the function found in the render map. If the vector is empty, no objects were found.</returns>
	virtual std::vector<std::pair<GameObject*, SDL_Texture*>> findInRenderMap(std::vector<std::pair<GameObject*, SDL_Texture*>> objects) = 0;

	/// <summary>
	/// Renders objects in the render map. Objects are rendered in layer->Z order, with layer 0 being rendered first and layer 4 being rendered last.
	/// </summary>
	virtual void render() = 0;

	};

