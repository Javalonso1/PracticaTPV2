#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
class PlayState;

class Laser : public SceneObject
{
private:
	Vector2D<int> Vel;	//Velocidad del láser
	bool friendly;		//Comprueba si es un láser amigo o enemigo
	bool ImAlive;		//Booleano de vida para borrarse después de un golpe	
public:
	Laser();			//Constructor vacío
	Laser(Point2D<int>&, int, bool, PlayState*);	//Constructor
	void Render() const override;
	void Update() override;		//Bucle principal
	bool hit(SDL_Rect*, bool) override;			//Método que anula 
	SDL_Rect* const getRect();	//Devuelve rect
	bool Friendly();		//Devuelve friendly
	void save(std::ostream&) const override;
};

