#pragma once
#include "checkML.h"
#include "Alien.h"
#include "Vector2D.h"
#include "texture.h"

class PlayState;
class Mothership;

class ShooterAlien : public Alien
{
private: 
	int shootlaser;		//Tiempo restante hasta siguiente láser
public:	
	ShooterAlien(Point2D<int>&, Texture*, int, PlayState*, int, Mothership*);
	bool Update() override;
};

