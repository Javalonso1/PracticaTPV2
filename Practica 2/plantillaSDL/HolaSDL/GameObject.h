#pragma once
#include "checkML.h"
#include <iostream>
#include "gameList.h"
class GameState;

class GameObject
{
protected:
	GameState* myGameState;
	GameList<GameObject, true>::anchor miIterador;
public:
	GameObject();
	GameObject(GameState*);
	virtual ~GameObject();
	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void save(std::ostream&) const = 0; 
	void setListAnchor(GameList<GameObject, true>::anchor);
};

