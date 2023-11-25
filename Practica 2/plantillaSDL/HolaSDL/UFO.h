#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include "texture.h"
enum Estado {
	Visible, Oculto,Destruido
};
class Game;
class UFO : public SceneObject
{
private:
	int MovingRight;
	Estado MiEstado;
	Texture* myTexture; //Textura de la nave			
	float tiempoEsp;	//Tiempo que debe esperar el UFO para aparecer de nuevo
public:
	UFO();			//Constructor vacío
	UFO(Point2D<int>, Texture*, Game*);	//Constructor
	void Render() const override;		//Renderizado
	bool Update() override;		//Bucle principal
	bool hit(SDL_Rect*, char) override;			//Método para ser golpeado	
	void setListIterator(std::list<SceneObject*>::iterator) override;
	void Destroyed();
};

