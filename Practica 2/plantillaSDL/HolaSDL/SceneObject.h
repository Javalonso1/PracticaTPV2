#pragma once 
#include "checkML.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include <list>

class SceneObject: public GameObject
{
protected:
	std::list<SceneObject*>::iterator miIterador;
	Point2D<int> pos;
	int width;
	int height;
	int vidas;
	SDL_Rect screenPos;
public:
	SceneObject();
	SceneObject(Point2D<int>,int,int,int, Game*);
	virtual ~SceneObject();
	virtual bool hit(SDL_Rect*, char) = 0;
	virtual void setListIterator(std::list<SceneObject*>::iterator) = 0;

};

