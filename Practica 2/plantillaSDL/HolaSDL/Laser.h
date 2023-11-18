#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
class Laser
{
private:
	Point2D<int> Pos;	//Posici�n del l�ser en l�gica
	Vector2D<int> Vel;	//Velocidad del l�ser
	bool friendly;		//Comprueba si es un l�ser amigo o enemigo
	SDL_Rect rect;		//Posicion del l�ser en pantalla
	bool ImAlive;		//Booleano de vida para borrarse despu�s de un golpe
public:
	Laser();			//Constructor vac�o
	Laser(Point2D<int>&, Vector2D<int>&, bool);	//Constructor
	void Render(SDL_Renderer*);
	bool Update();		//Bucle principal
	void Hit();			//M�todo que anula 
	SDL_Rect const getRect();	//Devuelve rect
	bool const Friendly();		//Devuelve friendly
};

