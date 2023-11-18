#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
class Laser
{
private:
	Point2D<int> Pos;	//Posición del láser en lógica
	Vector2D<int> Vel;	//Velocidad del láser
	bool friendly;		//Comprueba si es un láser amigo o enemigo
	SDL_Rect rect;		//Posicion del láser en pantalla
	bool ImAlive;		//Booleano de vida para borrarse después de un golpe
public:
	Laser();			//Constructor vacío
	Laser(Point2D<int>&, Vector2D<int>&, bool);	//Constructor
	void Render(SDL_Renderer*);
	bool Update();		//Bucle principal
	void Hit();			//Método que anula 
	SDL_Rect const getRect();	//Devuelve rect
	bool const Friendly();		//Devuelve friendly
};

