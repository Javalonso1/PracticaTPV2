#pragma once
#include "checkML.h"
#include "gameList.h"
#include "GameObject.h"
#include "SDL_image.h"

class Game;

class GameState
{
protected:
	Game* myGame;
	GameList<GameObject, true> pizza;
public:
	GameState(Game*);
	virtual ~GameState() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void HandleEvents() = 0;
	void addEventListener();
	void addObject();
	SDL_Renderer* getRenderer();
};

