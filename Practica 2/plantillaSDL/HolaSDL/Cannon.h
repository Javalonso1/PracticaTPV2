#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
class Game;
class Cannon
{
private:
	Point2D<int> Pos;	//Vector2D que indica la posici�n de la nave
	Texture* myTexture; //Textura de la nave
	Game* myGame;		//Referencia al juego
	int DirecMov;		//
	bool dispara;		//Indica que debe disparar
	int vidas;			//Vidas restantes
	float tiempoRes;	//Timer que controla la velocidad de disparo de la nave
	float tiempoEsp;	//Tiempo que debe esperar la nave para disparar de nuevo
	SDL_Rect rect;		//Rect�ndulo con posici�n y tama�o para el render
public:
	Cannon();			//Constructor vac�o
	Cannon(Point2D<int>*, Texture*, Game*, float);	//Constructor
	void Render();		//Renderiza
	bool Update();		//Bucle principal
	bool Hit(SDL_Rect*, char);			//M�todo para recibir da�o cuando es golpeado
	void handleEvent(int, bool);	//Usado para manejar eventos
	SDL_Rect const getRect();		//Devuelve el rect
};

