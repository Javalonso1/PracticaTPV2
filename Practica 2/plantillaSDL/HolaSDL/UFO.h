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
	UFO();			//Constructor vac�o
	UFO(Point2D<int>, Texture*, Game*, int, int, int);	//Constructor
	void Render() const override;		//Renderizado
	bool Update() override;		//Bucle principal
	bool hit(SDL_Rect*, bool) override;			//M�todo para ser golpeado	
	void save(std::ostream&) const override;
};

