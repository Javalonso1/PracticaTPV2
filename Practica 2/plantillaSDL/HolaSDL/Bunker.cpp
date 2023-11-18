#include "checkML.h"
#include "Bunker.h"
#include "Vector2D.h"
#include "texture.h"
Bunker::Bunker() : Pos(), vidas(), myTexture() {}	//Constructor vacío del bunker
Bunker::Bunker(Point2D<int>& a, Texture& b) : Pos(a), vidas(4), myTexture(&b) {	//Constructor con valores
	rect.h = myTexture->getFrameHeight();	//Inicializa su rect completamente, ya que no va a variar de posición en toda la partida
	rect.w = myTexture->getFrameWidth();
	rect.x = Pos.getX();
	rect.y = Pos.getY();
}
void Bunker::Render() {	//Renderizado del bunker
	if (Update()) {	//Si sigue con vidas (para evitar que el [4-vidas] de accidentalmente 5)
		(*myTexture).renderFrame(rect, 0, 4 - vidas);	//Renderiza el bunker
	}
}
bool Bunker::Update() {	//Devuelve si aún tiene vidas
	return vidas > 0;
}
void Bunker::Hit() {	//Si es golpeado, pierde una de sus vidas
	vidas--;	
}
SDL_Rect const Bunker::getRect() {	//Método que devuelve la hitbox del bunker
	return rect;
}