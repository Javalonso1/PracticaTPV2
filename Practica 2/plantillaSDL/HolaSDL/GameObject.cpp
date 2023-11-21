#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "GameObject.h"
#include "Game.h"

GameObject::GameObject() : myGame() {};
GameObject::GameObject(Game* gayme) : myGame(gayme) {};

GameObject::~GameObject() {

}