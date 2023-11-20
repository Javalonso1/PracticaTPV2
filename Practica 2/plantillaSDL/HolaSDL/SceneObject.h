#pragma once 
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "checkML.h"

class SceneObject: public GameObject
{
protected:
	Point2D<int> pos;
	int width;
	int height;
	int vidas;
	SDL_Rect* screenPos;
public:
	SceneObject();
	SceneObject(Point2D<int>,int,int,int, Game*);
	~SceneObject();
	bool hit(SDL_Rect*, char);
};

