#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include "texture.h"
#include "EventHandler.h"

class PlayState;
class Cannon : public SceneObject, public EventHandler
{
private:	
	Texture* myTexture; //Textura de la nave	
	Texture* Escudo; //Textura de la nave	
	int DirecMov;		//
	bool dispara;		//Indica que debe disparar	
	float tiempoRes;	//Timer que controla la velocidad de disparo de la nave
	float tiempoEsp;	//Tiempo que debe esperar la nave para disparar de nuevo	
	int invencible;
public:
	Cannon();			//Constructor vacío
	Cannon(Point2D<int>, Texture*, PlayState*, float, float, Texture*);	//Constructor
	void Render() const override;		//Renderizado
	void Update() override;		//Bucle principal
	bool hit(SDL_Rect*, bool, bool) override;			//Método para ser golpeado
	//void handleEvent(int, bool);	//Usado para manejar eventos	
	void save(std::ostream&) const override;
	void handleEvent(const SDL_Event&) override;	
};

