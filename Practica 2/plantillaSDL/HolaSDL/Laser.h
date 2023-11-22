#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"

class Laser : public SceneObject
{
private:
	Vector2D<int> Vel;	//Velocidad del l�ser
	bool friendly;		//Comprueba si es un l�ser amigo o enemigo
	bool ImAlive;		//Booleano de vida para borrarse despu�s de un golpe	
public:
	Laser();			//Constructor vac�o
	Laser(Point2D<int>&, Vector2D<int>&, bool, Game*);	//Constructor
	void Render() const override;
	bool Update() override;		//Bucle principal
	bool hit(SDL_Rect*, char) override;			//M�todo que anula 
	bool Hit();
	SDL_Rect* const getRect();	//Devuelve rect
	bool const Friendly();		//Devuelve friendly
};

