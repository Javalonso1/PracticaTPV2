#include "checkML.h"
#include "Bomba.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"
Vector2D<int> Vel = Vector2D<int>(0, 15);		//Crea un vector que ser� la velocidad al l�ser;	//Velocidad

Bomba::Bomba(Point2D<int>& a, Texture* b, PlayState* gayme) :Pos(a), vidas(2), myTexture(b), SceneObject(a, b->getFrameWidth(), b->getFrameHeight(), 4, gayme) {}	//Constructor con valores{};

void Bomba::Render() const {	//Render
	if (vidas > 0) {
		(*myTexture).renderFrame(screenPos, 0, 0);	//Renderiza el bunker
	}
}
void Bomba::Update() {	//Update		
	pos = pos + Vel;	//Avanza
	screenPos.x = pos.getX();	//Modifica el rect seg�n su posici�n
	screenPos.y = pos.getY();	
	if (myPlayState->CheckColisions(&screenPos, false, false)) {		
		vidas--;
		if(vidas <=0)myPlayState->HasDied(terador);
	}
}
bool Bomba::hit(SDL_Rect* rect, bool fren, bool a) {		//M�todo al que se llama cuando choca con algo		
	/*if (SDL_HasIntersection(rect, &screenPos) && fren != friendly) {
		return true;
	}
	else {
		return false;
	}*/
	return false;
}

SDL_Rect* const Bomba::getRect() {	//M�todo que devuelve su rect
	return &screenPos;
}

void Bomba::save(std::ostream& a) const {
	a << "7 " << pos.getX() << " " << pos.getY();
}