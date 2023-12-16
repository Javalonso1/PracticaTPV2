#include "Button.h"
#include "texture.h"
#include "GameObject.h"

Button::Button(Texture* tex, int x, int y) : myTexture(tex) {
	screenPos = SDL_Rect();
	screenPos.x = x;
	screenPos.y = y;
	screenPos.h = myTexture->getFrameHeight();
	screenPos.w = myTexture->getFrameWidth();
};

Button::~Button() {

}

void Button::Render() const {
	(*myTexture).renderFrame(screenPos, 0, 0);
}

void Button::Update() {

}

void Button::save(std::ostream&) const {

}