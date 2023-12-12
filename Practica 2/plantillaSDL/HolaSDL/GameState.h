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
	void update();
	void render();
	void handleEvent();
	void addEventListener();
	void addObject();
	SDL_Renderer* getRenderer();
};

