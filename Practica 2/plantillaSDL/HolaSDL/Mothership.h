#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "checkML.h"
#include <vector>
#include "Alien.h"

class Game;

class Mothership : public GameObject
{
	private:	
		int level;
		int direction;
		bool wall;
		bool move;
		bool landed;

		int livingAliens;
	public:
		Mothership();
		Mothership(Game*, int);
		int getDirection() const;
		bool shouldMove() const;
		void cannotMove();
		void AlienDied();
		void AlienLanded();
		bool haveLanded() const; 
		int getAlienCount() const;

		void Update();
};

