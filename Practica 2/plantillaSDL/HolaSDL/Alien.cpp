#include "checkML.h"
#include "Alien.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"
#include "Mothership.h"
#include "GameObject.h"
#include "SceneObject.h"

const int Velocidad = 15;			//Constante que indica cuanto se mueve el alien
//const int LaserDesplazacion = 15;	//Pequeño número usado para centrar el láser respeto al alien
//const int velLaser = 8;				//Velocidad que el alien le da al láser en su construtor
const int BordeD = 790;				//Constante que indica cuál es el borde derecho de la ventana
const int BordeI = 10;				//Constante que indica cuál es el borde izquierdo de la ventana
const int points = 10;

Alien::Alien() : myTexture(), subtipo(), ImAlive(), frame(), SceneObject(), ReduceFrames(), numberFrames(), minimoAltura(), myMother() {}	//Constructor vacío
Alien::Alien(Point2D<int>& a, Texture* b, int d, Game* f, int h, Mothership* m) : subtipo(d), SceneObject(a, b->getFrameWidth(), b->getFrameHeight(), 1, f),
																					ImAlive(true), frame(true), ReduceFrames(0), numberFrames(7),
																					minimoAltura(h), myMother(m), myTexture(b) {//Constuctor del alien
	screenPos->h = myTexture->getFrameHeight();	//Le da altura y anchura a su rect
	screenPos->w = myTexture->getFrameWidth();	
	myMother->assignAlien();
	//shootlaser = (*myGame).getRandomRange(6,180);	//Da un valor aleatorio al tiempo de espera para disparar láser
}
void Alien::Render() const{	//Renderizado
	if (frame) (*myTexture).renderFrame(*screenPos, subtipo, 0);	//Renderiza el alien
	else (*myTexture).renderFrame(*screenPos, subtipo, 1);
		
}
bool Alien::Update() {	//Update		
	if (myMother->shouldMove()) {
		frame = !frame;		//Cambia a su siguiente frame para la animación

		int mov = myMother->getDirection() * Velocidad;	//Pilla el movimiento del alien en el eje x
		Vector2D a(mov, 0);
		if (!myMother->shouldVertical()) {
			pos = pos + a;	//Aplica el movimiento horizontal			
			if (pos.getX() > BordeD - myTexture->getFrameWidth()) myMother->cannotMove();	//Detecta si choca con un borde
			if (pos.getX() < BordeI) myMother->cannotMove();
		}
		else {
			VerticalMove(10);
		}
	}
	/*if (subtipo == 0 && shootlaser <= 0) {	//si el timer para disparar el laser llega a 0, dispara un laser
		Point2D<int> g(Pos.getX() + LaserDesplazacion, Pos.getY());
		Vector2D<int> vel(0, velLaser);
		Laser xdd(g, vel, false);	//Crea el láser
		//myGame->fireLaser(&xdd);	//Se lo pasa al Game para que lo meta en su vector

		//shootlaser = (*myGame).getRandomRange(30, 180);	//Da un valor random de nuevo al timer
	}
	else {
		//shootlaser--;
	}*/
	screenPos->x = pos.getX();	//Le da la posición a su rect
	screenPos->y = pos.getY();
	return ImAlive;	//Devuelve true si sigue vivo, y false si ha sido golpeado
}
bool Alien::hit(SDL_Rect* laser, char frien) {	//Si es golpeado
	if (frien) {
		if (SDL_HasIntersection(laser, screenPos)) {
			ImAlive = false;
			myMother->AlienDied(points * (3 - subtipo));
			return true;
		}
		else {
			return false;
		}
	}
	else return false;
}
SDL_Rect* const Alien:: getRect() {	//Método que devuelve la hitbox del alien
	return screenPos;
}
void Alien::AumentVel() {	//Método que reduze la cantidad de tics que tienen que pasar para que el alien se mueva
	if (numberFrames > 1) numberFrames -=2;
}

void Alien::VerticalMove(int y) {	//Método al que se llama para que el alien descienda al chocar con un borde
	Vector2D a(0, y);
	pos = pos + a;	//Se cambia la posición
	if (pos.getY() > minimoAltura) (*myGame).EndGame();	//Si ha alcanzado la altura de la nave, eso es que el jugador ha perdido, y el juego termina

}
void Alien::setListIterator(std::list<SceneObject*>::iterator it) {
	miIterador = it;
}
void Alien::save(std::ostream& a) const {
	a << "1 " << pos.getX() << " " << pos.getY() << " " << subtipo;
}