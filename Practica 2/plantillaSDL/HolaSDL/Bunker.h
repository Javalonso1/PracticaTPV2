#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "PlayState.h"

class PlayState;

class Bunker : public SceneObject
{
private:
	Point2D<int> Pos;	//Posici�n en l�gica
	int vidas;			//Golpes restantes al bunker
	Texture* myTexture;	//Textura 

public:
	Bunker();			//Constructor vac�o
	Bunker(Point2D<int>&, Texture&, PlayState*, int);	//Constructor
	void Render() const override;		//Renderizado
	void Update() override;		//Bucle Principal
	bool hit(SDL_Rect*, bool, bool) override;			//M�todo para ser golpeado
	SDL_Rect* const getRect();	//Devuelve rect
	void save(std::ostream&) const override;
};

