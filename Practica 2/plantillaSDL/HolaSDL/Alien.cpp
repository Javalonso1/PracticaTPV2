#include "checkML.h"
#include "Alien.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"
#include "Mothership.h"
#include "GameObject.h"
#include "SceneObject.h"

const int Velocidad = 15;			//Constante que indica cuanto se mueve el alien
const int BordeD = 790;				//Constante que indica cuál es el borde derecho de la ventana
const int BordeI = 10;				//Constante que indica cuál es el borde izquierdo de la ventana
const int points = 10;				//Puntos base de cada alien
const int speedUp = 1;				//Incremento de velocidad al chocar con un borde
const int vertical = 20;			//Velocidad de bajada cuando chocan con un borde
const int maxPoints = 3;
const int vida = 1;

Alien::Alien() : myTexture(), subtipo(), frame(), SceneObject(), minimoAltura(), myMother() {}	//Constructor vacío
Alien::Alien(Point2D<int> a, Texture* b, int d, PlayState* f, int h, Mothership* m) : subtipo(d), SceneObject(a, b->getFrameWidth(), b->getFrameHeight(), vida, f),
																					frame(true), minimoAltura(h), 
																					myMother(m), myTexture(b) {//Constuctor del alien
	screenPos.h = myTexture->getFrameHeight();	//Le da altura y anchura a su rect
	screenPos.w = myTexture->getFrameWidth();	
	myMother->assignAlien();
}
void Alien::Render() const{	//Renderizado
	if (frame) (*myTexture).renderFrame(screenPos, subtipo, 0);	//Renderiza el alien
	else (*myTexture).renderFrame(screenPos, subtipo, 1);
		
}
void Alien::Update() {	//Update		
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
			VerticalMove(vertical);
		}
	}
	screenPos.x = pos.getX();	//Le da la posición a su rect
	screenPos.y = pos.getY();
}
bool Alien::hit(SDL_Rect* laser, bool frien, bool a) {	//Si es golpeado
	if (a) {
		return false;
	}
	else {
		if (frien && SDL_HasIntersection(laser, &screenPos)) {
			myPlayState->HasDied(terador);
			myMother->AlienDied(points * (maxPoints - subtipo));
			return true;
		}
		else return false;
	}
}
SDL_Rect* const Alien:: getRect() {	//Método que devuelve la hitbox del alien
	return &screenPos;
}

void Alien::VerticalMove(int y) {	//Método al que se llama para que el alien descienda al chocar con un borde
	Vector2D a(0, y);
	pos = pos + a;	//Se cambia la posición
	if (pos.getY() > minimoAltura) (*myPlayState).EndGame(false);	//Si ha alcanzado la altura de la nave, eso es que el jugador ha perdido, y el juego termina

}

void Alien::save(std::ostream& a) const { //Método de guardado del alien. Guarda su posición y su tipo
	a << "1 " << pos.getX() << " " << pos.getY() << " " << subtipo;
}