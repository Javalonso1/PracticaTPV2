#include "checkML.h"
#include "UFO.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"
#include "Bomba.h"
#include "Escudo.h"

const int BordeD = 850;				//Constante que indica cuál es el borde derecho de la ventana
const int BordeI = -50;				//Constante que indica cuál es el borde izquierdo de la ventana
const int espera = 50;				//Tiempo que permanece el ovni fuera de la pantalla. Constante porque no nos funciona el random
const int velocidad = 5;			//Velocidad horizontal del alien
const int Velocity = 1;

const int bomTexIndx = 15;
const int shiTexIndx = 17;

UFO::UFO() : MiEstado(), SceneObject(), tiempoEsp(){}
UFO::UFO(Point2D<int> a, Texture* b, PlayState* c, int d, int e, int f) : myTexture(b), tiempoEsp(e), MiEstado((Estado)f), SceneObject(a, b->getFrameWidth(), b->getFrameHeight(), d, c), MovingRight(-1){}

void UFO::Render() const {	//Render
	if(MiEstado == Visible)(*myTexture).renderFrame(screenPos, 0, 0);	//Renderiza la nave
	else if (MiEstado == Destruido && MovingRight !=0)(*myTexture).renderFrame(screenPos, 0, 1);	//Renderiza la nave
}

void UFO::Update() {		//Update	
	if (MiEstado == Oculto) {
		tiempoEsp--;
		if (tiempoEsp <= 0) {
			MiEstado = Visible;
			if (MovingRight == Velocity) {
				MovingRight = -1*Velocity;				
			}
			else if (MovingRight == -1 * Velocity) {
				MovingRight = Velocity;
			}
		}
	}
	else if (MiEstado == Visible) {		
		Vector2D a(velocidad * MovingRight, 0);
		pos = pos + a;
		if (MovingRight == Velocity && pos.getX() > BordeD - myTexture->getFrameWidth()) 
		{ 
			MiEstado = Oculto; 
			tiempoEsp = espera;// myGame->getRandomRange(100, 280);
		}
		if (MovingRight == -1 *Velocity&& pos.getX() < BordeI) {
			MiEstado = Oculto;
			tiempoEsp = espera;// myGame->getRandomRange(100, 280);
		}

	}if (MiEstado == Destruido) {
		MovingRight = 0;		
	}


	randomizador++;
	if (randomizador == 3) randomizador = 0;
	screenPos.x = pos.getX();	//Le da la posición a su rect
	screenPos.y = pos.getY();
}

bool UFO::hit(SDL_Rect* laser, bool frien, bool a) {	//Si es golpeado
	if (MiEstado == Visible && SDL_HasIntersection(laser, &screenPos) && frien) {
		MiEstado = Destruido;
		Gamble();
		return true;
	}
	else return false;
}

void UFO::save(std::ostream& a) const {
	a << "5 " << pos.getX() << " " << pos.getY() << " " << vidas << " " << MiEstado << " " << tiempoEsp;
}
void UFO::Gamble() {
	if (randomizador == 0) {
		Bomba* b = new Bomba(pos, myPlayState->returnText(bomTexIndx), myPlayState);
		myPlayState->fireLaser(b);
	}
	else if (randomizador == 1) {
		Escudo* b = new Escudo(pos, myPlayState->returnText(shiTexIndx), myPlayState);
		myPlayState->fireLaser(b);
	}	
}