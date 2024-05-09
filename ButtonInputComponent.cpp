#include "ButtonInputComponent.h"

InputComponent* ButtonInputComponent::getInputComponent()
{
	return this;
}

void ButtonInputComponent::handleInput(SDL_Event event)
{}

void ButtonInputComponent::handleInput(SDL_Event event, Button& button, IMenuState* state, SceneEscMenu* scene)
{
		// Get the current mouse coordinates
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		// Determine whether or not a button was clicked.
		if ((mouseX > button.getDimensions()->x) && (mouseX < button.getDimensions()->x + button.getDimensions()->w) && (mouseY > button.getDimensions()->y) && (mouseY < button.getDimensions()->y + button.getDimensions()->h))
		{
			// button clicked
			onClick(button, state, scene);
		}	
}

void ButtonInputComponent::onClick()
{}

void ButtonInputComponent::onClick(Button& button)
{}

void ButtonInputComponent::onClick(Button& button, IMenuState* state, SceneEscMenu* scene)
{
	std::cout << "Button " << button.type << " clicked!\n";
	// Send the button type back to the state
	switch (button.type)
	{
	case 0:
		state->changeState(scene, "Options");
		break;
	case 1:
		state->changeState(scene, "Back");
		break;
	case 2:
		state->changeState(scene, "ExitGame");
		break;
	case 3:
		state->changeState(scene, "Yes");
		break;
	case 4:
		state->changeState(scene, "No");
		break;
	case 5:
		state->changeState(scene, "Resolution");
		break;
	case 6:
		state->changeState(scene, "1024");
		break;
	case 7:
		state->changeState(scene, "1920");
		break;
	}
}

void ButtonInputComponent::onHover()
{}

void ButtonInputComponent::onKeyPress()
{}