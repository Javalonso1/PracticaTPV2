#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"

class Laser : public SceneObject
{
private:
	Vector2D<int> Vel;	//Velocidad del láser
	bool friendly;		//Comprueba si es un láser amigo o enemigo
	bool ImAlive;		//Booleano de vida para borrarse después de un golpe	
public:
	Laser();			//Constructor vacío
	Laser(Point2D<int>&, Vector2D<int>&, bool, Game*);	//Constructor
	void Render() const override;
	bool Update() override;		//Bucle principal
	bool hit(SDL_Rect*, char) override;			//Método que anula 
	bool Hit();
	SDL_Rect* const getRect();	//Devuelve rect
	bool const Friendly();		//Devuelve friendly
};

