#include "SceneObject.h"
#include "checkML.h"


SceneObject::SceneObject() {}
SceneObject::SceneObject(Point2D<int> po, int wi, int he, int salud, Game* gayme) : pos(po), width(wi), height(he), vidas(salud), GameObject(gayme) {}

bool SceneObject::hit(SDL_Rect* laser, char friendly) {
	if (SDL_HasIntersection(laser, screenPos)) {
		//Llamar a HasDied con su posición
		return true;
	}
}