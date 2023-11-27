#pragma once
#include "Alien.h"
#include "Vector2D.h"
#include "texture.h"

class Game;
class Mothership;

class ShooterAlien : public Alien
{
private: 
	int shootlaser;		//Tiempo restante hasta siguiente l�ser
public:
	ShooterAlien();
	ShooterAlien(Point2D<int>&, Texture*, int, Game*, int, Mothership*);
	bool Update() override;
};

