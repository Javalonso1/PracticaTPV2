#include "checkML.h"
#include "Laser.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"

const int heigth = 10;	//constante que guarda cuanto de alto mide el l�ser
const int wide = 3;		//constante que gurada cuanto de ancho mide el l�ser

Laser::Laser() : Vel(), friendly(){}		//Constructor vac�o
Laser::Laser(Point2D<int>& a, Vector2D<int>& b, bool c, Game* gayme): Vel(b), friendly(c), SceneObject(a, wide, heigth, 0, gayme){	//Constructor con valores para el l�ser
	ImAlive = true;
}
void Laser::Render() const {	//Render
	screenPos->x = pos.getX();	//Modifica el rect seg�n su posici�n
	screenPos->y = pos.getY();	
	if (!friendly)SDL_SetRenderDrawColor(myGame->getRenderer(), 255, 0, 0, 255);	//Si es un l�ser de la nave, se colorea de verde
	else SDL_SetRenderDrawColor(myGame->getRenderer(), 0, 255, 0, 255);		//Si es un l�ser de un alien, se colorea de rojo
	SDL_RenderFillRect(myGame->getRenderer(),screenPos);	//Se dibuja un rect�ngulo de ese color
}
bool Laser::Update() {	//Update
	pos = pos + Vel;	//Avanza
	myGame->CheckColisions(screenPos, friendly, this);
	return ImAlive;		//Devuelve true mientras no haya chocado con nada a�n
}
bool Laser::hit(SDL_Rect*, char) {		//M�todo al que se llama cuando choca con algo		
	return false;
}
bool Laser::Hit() {
	ImAlive = false;
	return true;
}
SDL_Rect* const Laser::getRect() {	//M�todo que devuelve su rect
	return screenPos;
}
bool const Laser::Friendly() {	//M�todo que devuelve true si es un l�ser lanzado por la nave, y false en cualquier otro caso
	return friendly;
}
void Laser::setListIterator(std::list<SceneObject*>::iterator it) {
	miIterador = it;
}