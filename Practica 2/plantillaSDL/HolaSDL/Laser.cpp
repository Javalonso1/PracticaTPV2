#include "checkML.h"
#include "Laser.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"

const int heigth = 10;	//constante que guarda cuanto de alto mide el láser
const int wide = 3;		//constante que gurada cuanto de ancho mide el láser
const int maxTam = 600;
const int minTam = 0;

Laser::Laser() : Vel(), friendly(){}		//Constructor vacío
Laser::Laser(Point2D<int>& a,int b, bool c, PlayState* gayme): friendly(c), SceneObject(a, wide, heigth, 0, gayme){	//Constructor con valores para el láser
	ImAlive = true;
	Vel = Vector2D<int> (0, b);		//Crea un vector que será la velocidad al láser
}
void Laser::Render() const {	//Render
	if (!friendly)SDL_SetRenderDrawColor(myPlayState->getRenderer(), 255, 0, 0, 255);	//Si es un láser de la nave, se colorea de verde
	else SDL_SetRenderDrawColor(myPlayState->getRenderer(), 0, 255, 0, 255);		//Si es un láser de un alien, se colorea de rojo
	SDL_RenderFillRect(myPlayState->getRenderer(),&screenPos);	//Se dibuja un rectángulo de ese color	
}
void Laser::Update() {	//Update		
	pos = pos + Vel;	//Avanza	
	screenPos.x = pos.getX();	//Modifica el rect según su posición
	screenPos.y = pos.getY();	
	if (myPlayState->CheckColisions(&screenPos, friendly) || pos.getY() > maxTam || pos.getY() < minTam) {
		myPlayState->HasDied(miIterador);
	}
}
bool Laser::hit(SDL_Rect* rect, bool fren) {		//Método al que se llama cuando choca con algo		
	/*if (SDL_HasIntersection(rect, &screenPos) && fren != friendly) {
		return true;
	}
	else {
		return false;
	}*/
	return false;
}

SDL_Rect* const Laser::getRect() {	//Método que devuelve su rect
	return &screenPos;
}

bool Laser::Friendly() {	//Método que devuelve true si es un láser lanzado por la nave, y false en cualquier otro caso
	return friendly;
}

void Laser::save(std::ostream& a) const {
	a << "6 " << pos.getX() << " " << pos.getY() << " " << Vel.getY() << " " <<friendly;
}