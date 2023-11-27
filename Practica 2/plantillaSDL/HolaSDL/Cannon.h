#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include "texture.h"
class Game;
class Cannon : public SceneObject
{
private:	
	Texture* myTexture; //Textura de la nave	
	int DirecMov;		//
	bool dispara;		//Indica que debe disparar	
	float tiempoRes;	//Timer que controla la velocidad de disparo de la nave
	float tiempoEsp;	//Tiempo que debe esperar la nave para disparar de nuevo	
public:
	Cannon();			//Constructor vacío
	Cannon(Point2D<int>, Texture*, Game*, float, float);	//Constructor
	void Render() const override;		//Renderizado
	bool Update() override;		//Bucle principal
	bool hit(SDL_Rect*, char) override;			//Método para ser golpeado
	void handleEvent(int, bool);	//Usado para manejar eventos	
	void setListIterator(std::list<SceneObject*>::iterator) override;
	void save(std::ostream&) const override;
};

