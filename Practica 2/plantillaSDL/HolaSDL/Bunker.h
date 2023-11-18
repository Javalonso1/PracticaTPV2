#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
class Bunker
{
private:
	Point2D<int> Pos;	//Posición en lógica
	int vidas;			//Golpes restantes al bunker
	Texture* myTexture;	//Textura 
	SDL_Rect rect;		//Posición en pantalla
public:
	Bunker();			//Constructor vacío
	Bunker(Point2D<int>&, Texture&);	//Constructor
	void Render();		//Renderizado
	bool Update();		//Bucle Principal
	void Hit();			//Método para ser golpeado
	SDL_Rect const getRect();	//Devuelve rect
};

