#pragma once
#include <iostream>
#include <string>

class GameObject;

// Virtual class for mediating game objects
class IMediator
{
public:

	virtual ~IMediator() {};

	/// <summary>
	/// Notifies the mediator that a particular action has occurred on an object.
	/// </summary>
	/// <param name="sender">The object whose status has changed.</param>
	/// <param name="eString">The event string describing the action.</param>
	virtual void notify(GameObject* sender, std::string eString) = 0;
};

