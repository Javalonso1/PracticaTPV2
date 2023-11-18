#include "checkML.h"
#include "Laser.h"
#include "Vector2D.h"
#include "texture.h"

const int heigth = 10;	//constante que guarda cuanto de alto mide el láser
const int wide = 3;		//constante que gurada cuanto de ancho mide el láser

Laser::Laser() : Pos(), Vel(), friendly(){}		//Constructor vacío
Laser::Laser(Point2D<int>& a, Vector2D<int>& b, bool c):Pos(a), Vel(b), friendly(c){	//Constructor con valores para el láser
	rect.h = heigth;
	rect.w = wide;	
	ImAlive = true;
}
void Laser::Render(SDL_Renderer* renderer) {	//Render
	rect.x = Pos.getX();	//Modifica el rect según su posición
	rect.y = Pos.getY();	
	if(!friendly)SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);	//Si es un láser de la nave, se colorea de verde
	else SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);		//Si es un láser de un alien, se colorea de rojo
	SDL_RenderFillRect(renderer, &rect);	//Se dibuja un rectángulo de ese color
}
bool Laser::Update() {	//Update
	Pos = Pos + Vel;	//Avanza
	return ImAlive;		//Devuelve true mientras no haya chocado con nada aún
}
void Laser::Hit() {		//Método al que se llama cuando choca con algo
	ImAlive = false;	
}
SDL_Rect const Laser::getRect() {	//Método que devuelve su rect
	return rect;
}
bool const Laser::Friendly() {	//Método que devuelve true si es un láser lanzado por la nave, y false en cualquier otro caso
	return friendly;
}
