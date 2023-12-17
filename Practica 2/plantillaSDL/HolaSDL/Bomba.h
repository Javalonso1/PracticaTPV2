#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "texture.h"
class PlayState;

class Bomba : public SceneObject
{private:
	Point2D<int> Pos;	//Posici�n en l�gica	
	int vidas;
	Texture* myTexture;
public:
	Bomba(Point2D<int>&, Texture*, PlayState* gayme);
	void Render() const override;
	void Update() override;		//Bucle principal
	bool hit(SDL_Rect*, bool, bool) override;			//M�todo que anula 
	SDL_Rect* const getRect();	//Devuelve rect	
	void save(std::ostream&) const override;
};
