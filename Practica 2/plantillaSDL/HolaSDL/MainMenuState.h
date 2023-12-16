#pragma once
#include "checkML.h"
#include "GameState.h"
#include "texture.h"
#include "Button.h"
#include <list>

class Game;

class MainMenuState : public GameState
{
private:
	std::list<EventHandler*> listeners;
public:
	MainMenuState(Game*);
	~MainMenuState();
	void Update();
	void Render() const;
	void HandleEvents();
};

