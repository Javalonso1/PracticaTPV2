#pragma once
#include "checkML.h"
#include "GameState.h"
#include "Button.h"
#include "texture.h"
class EndState : public GameState
{
private:
	Texture* myTexture;
	SDL_Rect screenPos;
	std::list<EventHandler*> listeners;
	Button* Salir;
	Button* VolverMenu;

public:
	EndState(Game*, bool);
	~EndState();
	void Update();
	void Render() const;
	void HandleEvents();
	void Save() override;
};



