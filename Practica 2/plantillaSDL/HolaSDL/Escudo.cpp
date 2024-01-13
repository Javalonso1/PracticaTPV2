#include "checkML.h"
#include "Escudo.h"
#include "texture.h"
#include "PlayState.h"

Escudo::Escudo(Point2D<int>& a, Texture* b, PlayState* gayme) :Reward(a,b,gayme) {}	//Constructor con valores{};

void Escudo::Act() {
	myPlayState->InvincibleShip();
}

void Escudo::save(std::ostream& a) const {
	a << "8 " << pos.getX() << " " << pos.getY();
}
