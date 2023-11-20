#include "SceneObject.h"
#include "checkML.h"


SceneObject::SceneObject() : height(), width(), screenPos(), vidas() {}
SceneObject::SceneObject(Point2D<int> po, int wi, int he, int salud, Game* gayme) : pos(po), width(wi), height(he), vidas(salud), GameObject(gayme) {
	screenPos->x = pos.getX();
	screenPos->y = pos.getY();
	screenPos->w = width;
	screenPos->h = height;
}

bool SceneObject::hit(SDL_Rect* laser, char friendly) {
	if (SDL_HasIntersection(laser, screenPos)) {
		//Llamar a HasDied con su posición
		return true;
	}
}