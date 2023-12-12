#include "checkML.h"
#include "Bunker.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"

Bunker::Bunker() : Pos(), vidas(), myTexture() {}	//Constructor vac�o del bunker
Bunker::Bunker(Point2D<int>& a, Texture& b, PlayState* gayme, int i) : Pos(a), vidas(i), myTexture(&b), SceneObject(a, b.getFrameWidth(), b.getFrameHeight(), 4, gayme) {}	//Constructor con valores

void Bunker::Render() const {	//Renderizado del bunker
	if (vidas > 0) {
		(*myTexture).renderFrame(screenPos, 0, 4 - vidas);	//Renderiza el bunker
	}
}
bool Bunker::Update() {	//Devuelve si a�n tiene vidas	
	return vidas > 0;
}
bool Bunker::hit(SDL_Rect* laser,  bool frien) {	//Si es golpeado, pierde una de sus vidas
	if (SDL_HasIntersection(laser, &screenPos)) {
		vidas--;
		if (vidas == 0) {
			myPlayState->HasDied(miIterador);
		}
		return true;
	}
	else {
		return false;
	}
}
SDL_Rect* const Bunker::getRect() {	//M�todo que devuelve la hitbox del bunker
	return &screenPos;
}

void Bunker::save(std::ostream& a) const {
	a << "4 " << pos.getX() << " " << pos.getY() << " " << vidas;
}