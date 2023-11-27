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
		bool vertical;
		bool landed;
		int frames;
		int livingAliens;
	public:
		Mothership();
		Mothership(Game*, int, int, int);
		~Mothership();
		int getDirection() const;
		bool shouldMove() const;
		bool shouldVertical() const;
		
		void cannotMove();
		void assignAlien();
		void AlienDied();
		void AlienLanded();
		bool haveLanded() const; 
		int getAlienCount() const;

		void Render() const override;
		bool Update() override;
		void save(std::ostream&) const override;
};

