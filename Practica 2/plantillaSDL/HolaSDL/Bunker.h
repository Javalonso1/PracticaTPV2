#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
class Bunker
{
private:
	Point2D<int> Pos;	//Posici�n en l�gica
	int vidas;			//Golpes restantes al bunker
	Texture* myTexture;	//Textura 
	SDL_Rect rect;		//Posici�n en pantalla
public:
	Bunker();			//Constructor vac�o
	Bunker(Point2D<int>&, Texture&);	//Constructor
	void Render();		//Renderizado
	bool Update();		//Bucle Principal
	void Hit();			//M�todo para ser golpeado
	SDL_Rect const getRect();	//Devuelve rect
};

