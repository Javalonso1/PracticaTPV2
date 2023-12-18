#include "checkML.h"
#include "Mothership.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"

const int LEVEL = 2;
Mothership::Mothership() : direction(), landed(), level(), livingAliens(), move(), wall(), points() {};
Mothership::Mothership(PlayState* game, int a, int b, int c) : myPlayState(game), direction(a), landed(false), level(b), livingAliens(0), move(true), wall(false), frames(c), points(0) {}

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
	system("cls");
	livingAliens--;
	points += i;
	std::cout << points;
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

void Mothership::Update() {
	if (frames > level) {
		if (wall) {
			vertical = true;
			wall = false;
		}
		else if (vertical) {
			vertical = false;
			direction = -direction;
			if (level > LEVEL) {
				level -= LEVEL;
			}
		}
		move = true;
		frames = 0;
	}
	else {
		move = false;
		frames++;
	}
}
void Mothership::save(std::ostream& a) const {
	a << "3 " << direction << " " << level << " " << frames;
}