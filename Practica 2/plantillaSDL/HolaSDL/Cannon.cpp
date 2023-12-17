#include "checkML.h"
#include "Cannon.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"
const int LaserDesplazacion = 15;	//Pequeño número usado para centrar el láser respeto a la nave
const int velLaser = -5;			//Velocidad que la nave le da al láser en su construtor
const int movSpeed = 5;				//Velocidad a la que se mueve la nave

Cannon::Cannon() : myTexture(), DirecMov(), dispara(),  tiempoRes(), tiempoEsp(), SceneObject() {} //Constructor vacío
Cannon::Cannon(Point2D<int> a, Texture* b, PlayState* c, float d, float e) : myTexture(b), DirecMov(), dispara(false), tiempoRes(0), tiempoEsp(e),
SceneObject(a, b->getFrameWidth(), b->getFrameHeight(), d, c) { //Constructor con valores
	screenPos.h = myTexture->getFrameHeight();	//Le da altura y anchura a su rect
	screenPos.w = myTexture->getFrameWidth();
}
void Cannon::Render() const{	//Render
	(*myTexture).renderFrame(screenPos, 0, 0);	//Renderiza la nave
}
void Cannon::Update() {		//Update	
	if (DirecMov != 0) {	//Si el jugador le dice que se mueva en una dirección
		Vector2D a(DirecMov, 0);	//Le da ese valor al vector
		pos = pos + a;		//Cambia su posición de acuerdo con ello
		DirecMov = 0;
	}
	if (tiempoRes < tiempoEsp) {	//Timer que controla lo rápido que puede disparar la nave
		tiempoRes++;
		dispara = false;	//Si el jugador le dice que dispare anula este comando
	}
	else {
		if (dispara) {	//Si el jugador le dice que dispare
			Point2D<int> g(pos.getX()+ LaserDesplazacion, pos.getY());	//Crea un Point2D que será la posición del láser			
			Laser* a = new Laser(g, velLaser, true, myPlayState);		//Crea un láser con todos sus valores
			myPlayState->fireLaser(a);		//Le pasa el láser al Game
			tiempoRes = 0;		//Reinicia el timer
			dispara = false;
		}
	}
	screenPos.x = pos.getX();	//Le da la posición a su rect
	screenPos.y = pos.getY();
}

bool Cannon::hit(SDL_Rect* laser, bool frien) {	//Si es golpeado
	if (!frien && SDL_HasIntersection(laser, &screenPos)) {
		vidas--;			
		if (vidas <= 0) {
			myPlayState->EndGame();
		}
		return true;
	}
	else return false;
}

/*void Cannon::handleEvent(int mov, bool disparado) {		//Le pasan los inputs del jugador, y este método lo transforma en variables legibles en el Cannon
	DirecMov = mov*movSpeed;
	dispara = disparado;	
}*/

void Cannon::save(std::ostream& a) const {
	a << "0 " << pos.getX() << " " << pos.getY() << " " << vidas << " " << tiempoEsp;
}

void Cannon::handleEvent(const SDL_Event& ev) {
	switch (ev.type) {
	case SDL_KEYDOWN:
		switch (ev.key.keysym.sym) {
		case SDLK_LEFT:
			DirecMov = -movSpeed;
			break;
		case SDLK_RIGHT:
			DirecMov = movSpeed;
			break;
		case SDLK_SPACE:
			dispara = true;
			break;
		}
	}
}