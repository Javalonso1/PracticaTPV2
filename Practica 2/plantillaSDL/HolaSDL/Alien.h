#pragma once
#include "checkML.h"
#include "SceneObject.h"
#include "Vector2D.h"
#include "texture.h"
class Game;
class Mothership;

class Alien: public SceneObject
{
private:
	int ReduceFrames;	//Frame actual del alien, usado para variar velocidad
	bool frame;			//Frame actual de la animaci�n
		
	int subtipo;		//Subtipo de alien
	Texture* myTexture;	//Textura

	//Game* myGame;		//Referencia al juego
	Mothership* myMother;	//Referencia a mothership

	bool ImAlive;		//Booleano de vida
	//int shootlaser;		//Tiempo restante hasta siguiente l�ser
	int numberFrames;	//Frames de mundo que tienen que pasar para que ocurra un frame de alien
	int minimoAltura;	//Altura bajo la cual sucede game over
public:
	Alien();			//Constructor vac�o
	Alien(Point2D<int>&, Texture*, int, Game*, int, Mothership*);
	void Render() const override;		//Renderizado
	bool Update() override;		//Bucle principal
	bool hit(SDL_Rect*, char) override;			//M�todo para ser golpeado
	SDL_Rect* const getRect();	//Devuelve el rect
	void AumentVel();	//M�todo para acelerar a los aliens
	void VerticalMove(int);	//M�todo para que los aliens bajen
};

