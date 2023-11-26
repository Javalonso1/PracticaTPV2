#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"

class Bunker : public SceneObject
{
private:
	Point2D<int> Pos;	//Posición en lógica
	int vidas;			//Golpes restantes al bunker
	Texture* myTexture;	//Textura 

public:
	Bunker();			//Constructor vacío
	Bunker(Point2D<int>&, Texture&, Game*);	//Constructor
	void Render() const override;		//Renderizado
	bool Update() override;		//Bucle Principal
	bool hit(SDL_Rect*, char) override;			//Método para ser golpeado
	void setListIterator(std::list<SceneObject*>::iterator) override;
	SDL_Rect* const getRect();	//Devuelve rect
	void save(std::ostream&) const override;
};

