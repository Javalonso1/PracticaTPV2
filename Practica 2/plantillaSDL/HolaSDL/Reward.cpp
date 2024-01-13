#include "checkML.h"
#include "Reward.h"
#include "Vector2D.h"
#include "texture.h"
#include "PlayState.h"
Vector2D<int> Vel2 = Vector2D<int>(0, 5);		//Crea un vector que será la velocidad al láser;	//Velocidad

Reward::Reward(Point2D<int>& a, Texture* b, PlayState* gayme) :Pos(a), myTexture(b), SceneObject(a, b->getFrameWidth(), b->getFrameHeight(), 4, gayme) {}	//Constructor con valores{};

void Reward::Render() const {	//Render
	if (vidas > 0) {
		(*myTexture).renderFrame(screenPos, 0, 0);	//Renderiza el bunker
	}
}
void Reward::Update() {	//Update		
	pos = pos + Vel2;	//Avanza
	screenPos.x = pos.getX();	//Modifica el rect según su posición
	screenPos.y = pos.getY();
	if (myPlayState->CheckColisions(&screenPos, false, true)) {	
		Act();	//Void que ocurre cuando la nave recolecta la recompensa
		myPlayState->HasDied(terador);		
	}
}
bool Reward::hit(SDL_Rect* rect, bool fren, bool a) {		//Método al que se llama cuando choca con algo		
	return false;
}

SDL_Rect* const Reward::getRect() {	//Método que devuelve su rect
	return &screenPos;
}

