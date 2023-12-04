#pragma once
#include "checkML.h"
#include "gameList.h"
#include "GameObject.h"

class GameState
{
private: 
	GameList<GameObject, true> pizza;
public:
	GameState();
	~GameState();
	void update();
	void render();
	void handleEvent();
	void addEventListener();
	void addObject();
};

