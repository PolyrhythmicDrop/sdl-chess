#pragma once
#include "Scene.h"
#include "Button.h"
#include "Decoration.h"

class IMenuState;

class SceneEscMenu : public Scene
{

public:
	using activeCallback = std::function<void(bool const)>;
	
	bool active;
	
	// ** Buttons and objects **

	// Escape Menu Objects
	Decoration* _escMenuBg;
	Button* _optionsButton;
	// Back button, can be reused for other menus
	Button* _backButton;
	Button* _exitButton;

	// Exit Confirmation Menu Objects
	Decoration* _exitConfirmMenuBg;
	Button* _yes;
	Button* _no;

	// Resolution Menu Objects
	Decoration* _resoMenuBg;
	Button* _1024;
	Button* _1920;


	SceneEscMenu();
	~SceneEscMenu();

	std::map<int, GameObject*> _currentMenuObjects;

	// ** Event handler functions **

	// Subscribes to a specified SDL_EventType and then calls a function (made using a lambda function) in response. Be sure to UNSUBSCRIBE from the event after you no longer need to listen for the event.
	void subscribeToEventManager(EventManager& manager);
	// Unsubscribes for the event manager. Should be called at some point after every subscribeToEventManager call, when you no longer want to "listen" for the event.
	void unsubscribeToEventManager(EventManager& manager);

	// Gets the state of the active flag
	bool getStatus() const;
	void addListener(bool active, activeCallback callback);
	void removeListener(bool active);
	void sendStatus(bool active);

	// State functions
	inline IMenuState* getCurrentState() { return _currentState; };
	inline IMenuState* getPreviousState() { return _previousState; };

	void changeState();
	void setMenuState(IMenuState& newState);

	void buildMenu();

private:
	/// <summary>
	/// The current state of the escape menu scene. The states it can be in are:
	/// -InactiveMenuState 
	/// -InEscMenuState
	/// -InResoMenu
	/// -InExitConfirmation
	/// </summary>
	IMenuState* _currentState;

	IMenuState* _previousState;

	// List of listeners
	std::map<bool, std::vector<activeCallback>> _listenerList;
};

