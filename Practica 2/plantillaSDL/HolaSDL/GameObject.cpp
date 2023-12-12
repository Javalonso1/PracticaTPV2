#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "GameObject.h"
#include "Game.h"

GameObject::GameObject() : myGame() {};
GameObject::GameObject(GameState* gayme) : myGameState(gayme) {};

GameObject::~GameObject() {

}