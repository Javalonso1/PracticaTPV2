#pragma once 
#include "checkML.h"
#include "PlayState.h"
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
	SDL_Rect screenPos;
	PlayState* myPlayState;
public:
	int vidas;
	SceneObject();
	SceneObject(Point2D<int>,int,int,int, PlayState*);
	virtual ~SceneObject();
	virtual bool hit(SDL_Rect*, bool) = 0;
	void setListIterator(std::list<SceneObject*>::iterator);	
};

