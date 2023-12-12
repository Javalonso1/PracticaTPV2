#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"
#include "checkML.h"
#include <vector>
#include "Alien.h"

class PlayState;

class Mothership : public GameObject
{
	private:	
		PlayState* myPlayState;
		int level;
		int direction;
		bool wall;
		bool move;
		bool vertical;
		bool landed;
		int frames;
		int livingAliens;
		int points;
	public:
		Mothership();
		Mothership(PlayState*, int, int, int);
		~Mothership();
		int getDirection() const;
		bool shouldMove() const;
		bool shouldVertical() const;
		
		void cannotMove();
		void assignAlien();
		void AlienDied(int);
		void AlienLanded();
		bool haveLanded() const; 
		int getAlienCount() const;
		int getPoint() const;

		void Render() const override;
		bool Update() override;
		void save(std::ostream&) const override;


};

