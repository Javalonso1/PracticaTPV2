#include "SceneObject.h"


SceneObject::SceneObject() {}
SceneObject::SceneObject(Point2D<int> po, int wi, int he, int salud, Game* gayme) : pos(po), width(wi), height(he), vidas(salud), GameObject(gayme) {}

