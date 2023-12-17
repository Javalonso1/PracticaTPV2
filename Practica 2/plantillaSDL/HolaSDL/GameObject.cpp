#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "GameObject.h"
#include "GameState.h"
#include "gameList.h"

GameObject::GameObject() {};
GameObject::GameObject(GameState* gayme) : myGameState(gayme) {};

GameObject::~GameObject() {

}

void GameObject::setListAnchor(GameList<GameObject, true>::anchor tits) {
	miIterador = tits;
}