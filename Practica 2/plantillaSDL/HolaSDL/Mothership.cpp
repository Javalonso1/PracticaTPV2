#include "Mothership.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "Game.h"
#include "checkML.h"

Mothership::Mothership() : direction(), landed(), level(), livingAliens(), move(), wall(), points() {};
Mothership::Mothership(PlayState* game, int a, int b, int c) : GameObject(game), direction(a), landed(false), level(b), livingAliens(0), move(true), wall(false), frames(c), points(0) {}

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

void Mothership::AlienDied(int i) {
	livingAliens--;
	points += i;
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
int Mothership::getPoint() const {
	return points;
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
			if (level > 2) {
				level -= 2;
			}
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
void Mothership::save(std::ostream& a) const {
	a << "3 " << direction << " " << level << " " << frames;
}