#include "SceneObject.h"
#include "checkML.h"
#include "PlayState.h"

SceneObject::SceneObject() : height(), width(), screenPos(), vidas() {}
SceneObject::SceneObject(Point2D<int> po, int wi, int he, int salud, PlayState* gayme) : pos(po), width(wi), height(he), vidas(salud), myPlayState(gayme){
	screenPos = SDL_Rect();
	screenPos.x = pos.getX();
	screenPos.y = pos.getY();
	screenPos.w = width;
	screenPos.h = height;
}

SceneObject::~SceneObject() {

}

bool SceneObject::hit(SDL_Rect* laser, bool friendly) {
	if (SDL_HasIntersection(laser, &screenPos)) {
		return true;
	}
	else {
		return false;
	}
}

void SceneObject::setListIterator(std::list<SceneObject*>::iterator it) {
	miIterador = it;
}