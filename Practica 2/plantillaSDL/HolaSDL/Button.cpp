#include "Button.h"
#include "texture.h"
#include "GameObject.h"
#include <functional>
#include <list>

using Callback = std::function<void(void)>;

Button::Button(GameState* webios, Texture* tex, int x, int y) : myTexture(tex), GameObject(webios) {
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

void Button::save(std::ostream& estrin) const {

}

void Button::Connect(Callback segso) {
	myCallbacks.push_back(segso);
}

void Button::handleEvent(const SDL_Event& event) {
	if (true) {
		for (std::list<Callback>::iterator i = myCallbacks.begin(); i != myCallbacks.end(); i++) {
			(*i)();
		}
	}
}