#include "checkML.h"
#include "Cannon.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"
const int LaserDesplazacion = 15;	//Peque�o n�mero usado para centrar el l�ser respeto a la nave
const int velLaser = -5;			//Velocidad que la nave le da al l�ser en su construtor

Cannon::Cannon() : myTexture(), DirecMov(), dispara(),  tiempoRes(), tiempoEsp(), SceneObject() {} //Constructor vac�o
Cannon::Cannon(Point2D<int> a, Texture* b, Game* c, float d, float e) : myTexture(b), DirecMov(), dispara(false), tiempoRes(0), tiempoEsp(e), 
SceneObject(a, b->getFrameWidth(), b->getFrameHeight(), d, c) { //Constructor con valores
	screenPos.h = myTexture->getFrameHeight();	//Le da altura y anchura a su rect
	screenPos.w = myTexture->getFrameWidth();
}
void Cannon::Render() const{	//Render
	(*myTexture).renderFrame(screenPos, 0, 0);	//Renderiza la nave
}
bool Cannon::Update() {		//Update	
	if (DirecMov != 0) {	//Si el jugador le dice que se mueva en una direcci�n
		Vector2D a(DirecMov, 0);	//Le da ese valor al vector
		pos = pos + a;		//Cambia su posici�n de acuerdo con ello
		DirecMov = 0;
	}
	if (tiempoRes < tiempoEsp) {	//Timer que controla lo r�pido que puede disparar la nave
		tiempoRes++;
		dispara = false;	//Si el jugador le dice que dispare anula este comando
	}
	else {
		if (dispara) {	//Si el jugador le dice que dispare
			Point2D<int> g(pos.getX()+ LaserDesplazacion, pos.getY());	//Crea un Point2D que ser� la posici�n del l�ser			
			Laser* a = new Laser(g, velLaser, true, myGame);		//Crea un l�ser con todos sus valores
			myGame->fireLaser(a);		//Le pasa el l�ser al Game
			tiempoRes = 0;		//Reinicia el timer
			dispara = false;
		}
	}
	screenPos->x = pos.getX();	//Le da la posici�n a su rect
	screenPos->y = pos.getY();
	return(vidas > 0);	//Devuelve true mientras tenga al menos una vida a�n
}
bool Cannon::hit(SDL_Rect* laser, char frien) {	//Si es golpeado
	if (frien == false) {
		if (SDL_HasIntersection(laser, screenPos)) {
			vidas--;			
			if (vidas <= 0) myGame->EndGame();
			return true;
		}
		else {
			return false;
		}
	}
	else return false;
}
void Cannon::handleEvent(int mov, bool disparado) {		//Le pasan los inputs del jugador, y este m�todo lo transforma en variables legibles en el Cannon
	DirecMov = mov*5;
	dispara = disparado;	
}
void Cannon::setListIterator(std::list<SceneObject*>::iterator it) {
	miIterador = it;
}
void Cannon::save(std::ostream& a) const {
	a << "0 " << pos.getX() << " " << pos.getY() << " " << vidas << " " << tiempoEsp;
}