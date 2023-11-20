#pragma once
#include "checkML.h"
#include "GameObject.h"
#include "SceneObject.h"
#include "Vector2D.h"
#include "texture.h"
class Game;

class Alien: public SceneObject
{
private:
	int ReduceFrames;	//Frame actual del alien, usado para variar velocidad
	Point2D<int> Pos;	//Posici�n del alien en l�gica
	int subtipo;		//Subtipo de alien
	Texture* myTexture;	//Textura
	Game* myGame;		//Referencia al juego
	bool ImAlive;		//Booleano de vida
	bool frame;			//Frame actual de la animaci�n
	SDL_Rect rect;		//Posici�n en pantalla
	int shootlaser;		//Tiempo restante hasta siguiente l�ser
	int numberFrames;	//Frames de mundo que tienen que pasar para que ocurra un frame de alien
	int minimoAltura;	//Altura bajo la cual sucede game over
public:
	Alien();			//Constructor vac�o
	Alien(Point2D<int>&, Texture&, int, Game*, int);
	void Render();		//Renderizado
	bool Update();		//Bucle principal
	bool Hit();			//M�todo para ser golpeado
	SDL_Rect const getRect();	//Devuelve el rect
	void AumentVel();	//M�todo para acelerar a los aliens
	void VerticalMove(int);	//M�todo para que los aliens bajen
};

