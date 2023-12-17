#include "Button.h"
#include "texture.h"
#include "GameObject.h"
#include <functional>
#include <list>

using Callback = std::function<void(void)>;

Button::Button(GameState* webios, Texture* tex, int x, int y) : myTexture(tex), GameObject(webios), encima(false) {
	screenPos = SDL_Rect();
	screenPos.x = x;
	screenPos.y = y;
	screenPos.h = myTexture->getFrameHeight();
	screenPos.w = myTexture->getFrameWidth();
};

Button::~Button() {

}

void Button::Render() const {
	if (encima) {
		SDL_Color col;
		col.r = 0;
		col.b = 0;
		col.g = 255;
		myTexture->render(screenPos, col);
	}
	else {
		myTexture->render(screenPos);
	}
}

void Button::Update() {
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);
	encima = SDL_PointInRect(&point, &screenPos);
}

void Button::save(std::ostream& estrin) const {

}

void Button::Connect(Callback segso) {
	myCallbacks.push_back(segso);
}

void Button::handleEvent(const SDL_Event& ev) {
	if (ev.type == SDL_MOUSEBUTTONDOWN && encima) {
		for (std::list<Callback>::iterator i = myCallbacks.begin(); i != myCallbacks.end(); i++) {
			(*i)();
		}
	}
}