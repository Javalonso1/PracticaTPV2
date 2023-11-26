#include "checkML.h"
#include "UFO.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"
const int BordeD = 850;				//Constante que indica cuál es el borde derecho de la ventana
const int BordeI = -50;				//Constante que indica cuál es el borde izquierdo de la ventana

UFO::UFO() : MiEstado(), SceneObject(), tiempoEsp(){}
UFO::UFO(Point2D<int> a, Texture* b, Game* c) : myTexture(b), tiempoEsp(), MiEstado(Oculto), SceneObject(a, b->getFrameWidth(), b->getFrameHeight(), 10, c), MovingRight(-1)
{
	tiempoEsp =  50;//myGame->getRandomRange(100, 280);
}
void UFO::Render() const {	//Render
	if(MiEstado == Visible)(*myTexture).renderFrame(*screenPos, 0, 0);	//Renderiza la nave
	else if (MiEstado == Destruido && MovingRight !=0)(*myTexture).renderFrame(*screenPos, 0, 1);	//Renderiza la nave
}
bool UFO::Update() {		//Update	
	if (MiEstado == Oculto) {
		tiempoEsp--;
		if (tiempoEsp <= 0) {
			MiEstado = Visible;
			if (MovingRight == 1) {
				MovingRight = -1;				
			}
			else if (MovingRight == -1) {
				MovingRight = 1;
			}
		}
	}
	else if (MiEstado == Visible) {		
		Vector2D a(5 * MovingRight, 0);
		pos = pos + a;
		if (MovingRight == 1 && pos.getX() > BordeD - myTexture->getFrameWidth()) 
		{ 
			MiEstado = Oculto; 
			tiempoEsp = 50;// myGame->getRandomRange(100, 280);
		}
		if (MovingRight == -1 && pos.getX() < BordeI) {
			MiEstado = Oculto;
			tiempoEsp = 50;// myGame->getRandomRange(100, 280);
		}

	}if (MiEstado == Destruido) {
		MovingRight = 0;
		vidas--;
	}



	screenPos->x = pos.getX();	//Le da la posición a su rect
	screenPos->y = pos.getY();
	return(vidas > 0);	//Devuelve true mientras tenga al menos una vida aún
}
bool UFO::hit(SDL_Rect* laser, char frien) {	//Si es golpeado
	if (MiEstado == Visible) {
		if (SDL_HasIntersection(laser, screenPos)) {
			MiEstado = Destruido;
			return true;
		}
		else {
			return false;
		}
	}
	else return false;
}
void UFO::setListIterator(std::list<SceneObject*>::iterator it) {
	miIterador = it;
}
void UFO::save(std::ostream& a) const {
	a << "5 " << pos.getX() << " " << pos.getY() << " " << vidas << " " << MiEstado << " " << tiempoEsp;
}