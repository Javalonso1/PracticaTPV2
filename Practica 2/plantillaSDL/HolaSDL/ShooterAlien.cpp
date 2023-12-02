#include "ShooterAlien.h"
#include "Alien.h"
#include "Vector2D.h"
#include "texture.h"
#include "Laser.h"
#include "Game.h"
#include "Mothership.h"

const int LaserDesplazacion = 15;	//Pequeño número usado para centrar el láser respeto al alien
const int velLaser = 8;				//Velocidad que el alien le da al láser en su construtor
const int disp = 5;					//Tiempo para disparar, hecho constante porque no nos funciona el random por alguna razón

ShooterAlien::ShooterAlien() {};
ShooterAlien::ShooterAlien(Point2D<int>& a, Texture* b, int d, Game* f, int h, Mothership* m) : Alien(a, b, d, f, h, m), shootlaser(0) {};

bool ShooterAlien::Update()  {
	if (myMother->shouldMove()) {
		if (shootlaser <= 0) {	//si el timer para disparar el laser llega a 0, dispara un laser
			Point2D<int> g(pos.getX() + LaserDesplazacion, pos.getY());			
			Laser* xd = new Laser(g, velLaser, false, myGame);	//Crea el láser
			myGame->fireLaser(xd);	//Se lo pasa al Game para que lo meta en su vector
			//shootlaser = myGame->getRandomRange(30, 180);	//Da un valor random de nuevo al timer
			shootlaser = disp;
		}
		else {
			shootlaser--;
		}
	}
	return Alien::Update();
}