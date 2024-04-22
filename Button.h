#pragma once
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Window.h"
#include <array>
#include <iostream>

class Button
{
private:
	
	std::string _buttonName;
	SDL_Texture* _buttonTexture;
	SDL_Rect _buttonRect;
	std::string _buttonPath;
	int _buttonW;
	int _buttonH;
	int _buttonX;
	int _buttonY;

public:
	// Constructors
	Button(std::string name = "Button", std::string imgPath = "");


	/// <summary>
	/// Gets the texture for the button.
	/// </summary>
	/// <returns></returns>
	SDL_Texture* getButtonTexture();

	void setButtonTexture(SDL_Texture* texture);

	std::string getButtonPath();

	/// <summary>
	/// Creates a clip rectangle for the button (_buttonRect), and also initializes the button's W and H values to the rectangle's W & H.
	/// </summary>
	/// <param name="width">The width of the rectangle</param>
	/// <param name="height">The height of the rectangle</param>
	/// <param name="x">The X coordinate of the rectangle</param>
	/// <param name="y">The Y coordinate of the rectangle</param>
	void setButtonSourceRect(int x, int y, int width, int height);
	

	SDL_Rect getButtonSourceRect();

	/// <summary>
	/// Gets the string name of the button.
	/// </summary>
	/// <returns></returns>
	std::string getButtonName();

	// Button width getters and setters
	void setButtonWidth(int width);
	int getButtonWidth();

	// Button height getters and setters
	void setButtonHeight(int height);
	int getButtonHeight();

	void setButtonX(int x);
	int getButtonX();

	void setButtonY(int y);
	int getButtonY();



};

