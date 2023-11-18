#pragma once
#include "checkML.h"
#include <iostream>
class Game;

class GameObject
{
protected:
	Game* myGame;
public:
	GameObject();
	GameObject(Game*);
	~GameObject();
	void Render() const;
	void Update();
	void save(std::ostream&) const;
};

