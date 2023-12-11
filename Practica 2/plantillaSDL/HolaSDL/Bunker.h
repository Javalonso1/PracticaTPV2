#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"

class Game;

class Bunker : public SceneObject
{
private:
	Point2D<int> Pos;	//Posición en lógica
	int vidas;			//Golpes restantes al bunker
	Texture* myTexture;	//Textura 

public:
	Bunker();			//Constructor vacío
	Bunker(Point2D<int>&, Texture&, Game*, int);	//Constructor
	void Render() const override;		//Renderizado
	bool Update() override;		//Bucle Principal
	bool hit(SDL_Rect*, bool) override;			//Método para ser golpeado
	SDL_Rect* const getRect();	//Devuelve rect
	void save(std::ostream&) const override;
};

