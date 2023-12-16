#pragma once
#include "checkML.h"
#include <iostream>
class GameState;

class GameObject
{
protected:
//	GameState* myGameState;
public:
	GameObject();
	//GameObject(GameState*);
	virtual ~GameObject();
	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void save(std::ostream&) const = 0; 
};

