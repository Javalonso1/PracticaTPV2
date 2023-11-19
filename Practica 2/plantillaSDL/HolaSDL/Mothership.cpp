#include "Mothership.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"
#include "checkML.h"

Mothership::Mothership() {};
Mothership::Mothership(Game* game) : GameObject(game) {}

Mothership::~Mothership() {

}

int Mothership::getDirection() const{
	return direction;
}

bool Mothership::shouldMove() const {
	return moveH;
}

void Mothership::cannotMove() {
	moveH = false;
}

void Mothership::AlienDied(int pos) {
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
	if (moveH) {
		for (int i = 0; i < aliens.size(); i++) {
			if (!aliens[i].Update()) {

			}
		}
	}
	else {
		for (int i = 0; i < aliens.size(); i++) {
			//Mover a cada alien para abajo
		}
	}
}

void Mothership::Render() {
	for (int i = 0; i < aliens.size(); i++) {
		aliens[i].Render();
	}
}