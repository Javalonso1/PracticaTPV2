#pragma once
#include "checkML.h"
#include "GameState.h"
#include "texture.h"
#include "Button.h"

class Game;

class MainMenuState : public GameState
{
private:
	Button barry;
public:
	MainMenuState(Game*);
	~MainMenuState();
	void Update();
	void Render() const;
	void HandleEvents();
};

