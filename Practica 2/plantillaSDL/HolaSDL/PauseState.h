#pragma once
#include "checkML.h"
#include "GameState.h"
#include "PlayState.h"
#include "Button.h"
#include "texture.h"
#include <list>

class Game;

class PauseState : public GameState
{
private:
	PlayState* previous;

	std::list<EventHandler*> listeners;
	Button* Continuar;
	Button* VolverMenu;
	Button* GuardarPartida;	
public:
	PauseState(Game*);
	~PauseState();
	void Update();
	void Render() const;
	void HandleEvents();
	void Save() override;			
};


