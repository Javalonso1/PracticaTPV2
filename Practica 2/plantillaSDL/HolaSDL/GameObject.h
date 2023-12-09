#pragma once
#include "checkML.h"
#include "GameState.h"
#include <iostream>
class Game;

class GameObject
{
protected:
	Game* myGame;
	GameState* myGameState;
public:
	GameObject();
	GameObject(GameState*);
	virtual ~GameObject();
	virtual void Render() const = 0;
	virtual bool Update() = 0;
	virtual void save(std::ostream&) const = 0; 	
};

