#include "Mothership.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"
#include "checkML.h"

Mothership::Mothership() : direction(), landed(), level(), livingAliens(), move(), wall() {};
Mothership::Mothership(Game* game, int alive) : GameObject(game), direction(1), landed(false), level(10), livingAliens(alive), move(true), wall(false) {}

int Mothership::getDirection() const{
	return direction;
}

bool Mothership::shouldMove() const {
	return move;
}

void Mothership::cannotMove() {
	wall = true;
}

void Mothership::AlienDied() {
	//Llamar al alien en pos
}

void Mothership::AlienLanded() {
	landed = true;
}

bool Mothership::haveLanded() const {
	return landed;
}

int Mothership::getAlienCount() const{
	return livingAliens;
}

void Mothership::Update() {
	if (wall = true) {
		move = false;
		wall = false;
	}
	else if (move = false) {
		move = true;
	}
}