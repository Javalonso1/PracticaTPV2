#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
class Game;

class Mothership : public GameObject
{
	private:	
		int level;
	public:
		Mothership();
		Mothership(Game*);
		~Mothership();
		void getDirection() const;
		bool shouldMove() const;
		void cannotMove();
		void AlienDied();
		void AlienLanded();
		void haveLanded() const; 
		int getAlienCount() const;
};

