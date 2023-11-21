#include "Mothership.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"
#include "checkML.h"

Mothership::Mothership() : direction(), landed(), level(), livingAliens(), move(), wall() {};
Mothership::Mothership(Game* game) : GameObject(game), direction(1), landed(false), level(10), livingAliens(0), move(true), wall(false), frames(0) { }

Mothership::~Mothership() {

}

int Mothership::getDirection() const{
	return direction;
}

bool Mothership::shouldMove() const {
	return move;
}

bool Mothership::shouldVertical() const {
	return vertical;
}

void Mothership::cannotMove() {
	wall = true;
}

void Mothership::assignAlien() {
	livingAliens++;
}

void Mothership::AlienDied() {
	livingAliens--;
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

void Mothership::Render() const {

}

bool Mothership::Update() {
	if (frames > level) {
		if (wall) {
			vertical = true;
			wall = false;
		}
		else if (vertical) {
			vertical = false;
			direction = -direction;
		}
		move = true;
		frames = 0;
	}
	else {
		move = false;
		frames++;
	}
	return true;
}