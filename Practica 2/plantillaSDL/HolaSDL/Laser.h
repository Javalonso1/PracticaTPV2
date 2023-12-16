#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
class PlayState;

class Laser : public SceneObject
{
private:
	Vector2D<int> Vel;	//Velocidad del l�ser
	bool friendly;		//Comprueba si es un l�ser amigo o enemigo
	bool ImAlive;		//Booleano de vida para borrarse despu�s de un golpe	
public:
	Laser();			//Constructor vac�o
	Laser(Point2D<int>&, int, bool, PlayState*);	//Constructor
	void Render() const override;
	void Update() override;		//Bucle principal
	bool hit(SDL_Rect*, bool) override;			//M�todo que anula 
	SDL_Rect* const getRect();	//Devuelve rect
	bool Friendly();		//Devuelve friendly
	void save(std::ostream&) const override;
};

