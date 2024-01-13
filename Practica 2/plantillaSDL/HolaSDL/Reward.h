#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
class PlayState;

class Reward : public SceneObject
{
protected:
	Point2D<int> Pos;	//Posición en lógica		
	Texture* myTexture;
public:
	Reward(Point2D<int>&, Texture*, PlayState* gayme);
	void Render() const override;
	void Update() override;		//Bucle principal
	bool hit(SDL_Rect*, bool, bool) override;			//Método que anula 
	SDL_Rect* const getRect();	//Devuelve rect	
	virtual void Act() = 0; //Void que ocurre cuando la nave recolecta la recompensa
};

