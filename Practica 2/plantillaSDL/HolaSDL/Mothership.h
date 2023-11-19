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
		bool moveH;
		bool landed;

		int livingAliens;
		std::vector<Alien> aliens;
	public:
		Mothership();
		Mothership(Game*);
		~Mothership();
		int getDirection() const;
		bool shouldMove() const;
		void cannotMove();
		void AlienDied(int);
		void AlienLanded();
		bool haveLanded() const; 
		int getAlienCount() const;

		void Update();
		void Render();
};

