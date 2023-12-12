#pragma once
#include "checkML.h"
#include "SceneObject.h"
#include "Vector2D.h"
#include "texture.h"
class PlayState;
class Mothership;

class Alien: public SceneObject
{
protected:
	bool frame;			//Frame actual de la animación
		
	int subtipo;		//Subtipo de alien
	Texture* myTexture;	//Textura

	Mothership* myMother;	//Referencia a mothership

	int minimoAltura;	//Altura bajo la cual sucede game over
public:
	Alien();			//Constructor vacío
	Alien(Point2D<int>&, Texture*, int, PlayState*, int, Mothership*);
	void Render() const override;		//Renderizado
	virtual bool Update() override;		//Bucle principal
	bool hit(SDL_Rect*, bool) override;			//Método para ser golpeado
	SDL_Rect* const getRect();	//Devuelve el rect
	void VerticalMove(int);	//Método para que los aliens bajen
	void save(std::ostream&) const override;
};

