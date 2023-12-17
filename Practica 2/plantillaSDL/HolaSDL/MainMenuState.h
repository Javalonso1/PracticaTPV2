#pragma once
#include "checkML.h"
#include "GameState.h"
#include "Button.h"
#include "texture.h"
#include <list>

class Game;

class MainMenuState : public GameState
{
private:
	std::list<EventHandler*> listeners;
	Button* NuevaPartida;
	Button* CargarPartida;
	Button* Salir;
public:
	MainMenuState(Game*);
	~MainMenuState();
	void Update();
	void Render() const;
	void HandleEvents();
};

