#include "checkML.h"
#include "Cannon.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"
const int LaserDesplazacion = 15;	//Pequeño número usado para centrar el láser respeto a la nave
const int velLaser = -10;			//Velocidad que la nave le da al láser en su construtor

Cannon::Cannon() : Pos(), myTexture(), DirecMov(), myGame(), dispara(), vidas(), tiempoRes(), tiempoEsp() {} //Constructor vacío
Cannon::Cannon(Point2D<int>* a, Texture* b, Game* c, float d) : Pos(*a), myTexture(b), DirecMov(), myGame(c), dispara(false), vidas(3), tiempoRes(d), tiempoEsp(d) { //Constructor con valores
	rect.h = myTexture->getFrameHeight(); //Le da altura y anchura a su rect
	rect.w = myTexture->getFrameWidth();
}
void Cannon::Render() {	//Render
	rect.x = Pos.getX();	//Actualiza la posición de su rect
	rect.y = Pos.getY();		
	(*myTexture).renderFrame(rect, 0, 0);	//Renderiza la nave
}
bool Cannon::Update() {		//Update
	if (DirecMov != 0) {	//Si el jugador le dice que se mueva en una dirección
		Vector2D a(DirecMov, 0);	//Le da ese valor al vector
		Pos = Pos + a;		//Cambia su posición de acuerdo con ello
		DirecMov = 0;
	}
	if (tiempoRes < tiempoEsp) {	//Timer que controla lo rápido que puede disparar la nave
		tiempoRes++;
		dispara = false;	//Si el jugador le dice que dispare anula este comando
	}
	else {
		if (dispara) {	//Si el jugador le dice que dispare
			Point2D<int> g(Pos.getX()+ LaserDesplazacion, Pos.getY());	//Crea un Point2D que será la posición del láser
			Vector2D<int> vel(0, velLaser);		//Crea un vector que será la velocidad al láser
			Laser a(g, vel, true);		//Crea un láser con todos sus valores
			myGame->fireLaser(&a);		//Le pasa el láser al Game
			tiempoRes = 0;		//Reinicia el timer
			dispara = false;
		}
	}
	return(vidas > 0);	//Devuelve true mientras tenga al menos una vida aún
}
void Cannon::Hit() {	//Si es golpeado
	vidas--;	//Pierde una vida
}
void Cannon::handleEvent(int mov, bool disparado) {		//Le pasan los inputs del jugador, y este método lo transforma en variables legibles en el Cannon
	DirecMov = mov*10;
	dispara = disparado;	
}
SDL_Rect const Cannon::getRect() {	//Método que devuelve su hitbox
	return rect;
}