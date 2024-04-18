#pragma once
class Window
{
public:
	// Attributes
	
	// Window height and width
	int windowWidth { };
	int windowHeight { };

	//Constructors
	Window(int width = 640, int height = 480);

	// Methods

	// Get window width
	int getWindowWidth();

	// Get window height
	int getWindowHeight();
};

