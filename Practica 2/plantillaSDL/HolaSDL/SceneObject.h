#pragma once 
#include "checkML.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include <list>
#include "gameList.h"

class PlayState;
class SceneObject: public GameObject
{
protected:
	GameList<SceneObject>::anchor terador;
	PlayState* myPlayState;
	Point2D<int> pos;
	int width;
	int height;
	SDL_Rect screenPos;
	int vidas;
public:
	SceneObject();
	SceneObject(Point2D<int>,int,int,int, PlayState*);
	virtual ~SceneObject();
	virtual bool hit(SDL_Rect*, bool, bool) = 0;
	void setListAnchor(GameList<SceneObject>::anchor);
};

