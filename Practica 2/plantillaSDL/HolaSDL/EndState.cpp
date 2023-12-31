#include "checkML.h"
#include "EndState.h"
#include "GameState.h"
#include "Button.h"
#include "texture.h"
#include "MainMenuState.h"
#include "Game.h"
const int LogoPosX = 300;
const int LogoPosY = 135;

EndState::EndState(Game* e, bool a) : GameState(e) {	
	screenPos = SDL_Rect();
	screenPos.x = LogoPosX;
	screenPos.y = LogoPosY;	
	if (a) {
		myTexture = myGame->devuelveText(13);
	}
	else {
		myTexture = myGame->devuelveText(14);
	}
	screenPos.h = myTexture->getFrameHeight();
	screenPos.w = myTexture->getFrameWidth();

	VolverMenu = new Button(this, myGame->devuelveText(12), 230, 200);
	addEventListener(VolverMenu);
	VolverMenu->Connect([this]() {
		MainMenuState* playstate = new MainMenuState(myGame);
		myGame->pushState(playstate);
		});
	objects.push_back(VolverMenu);
	Salir = new Button(this, myGame->devuelveText(9), 350, 265);
	addEventListener(Salir);
	Salir->Connect([this]() {myGame->ExitGame(); });
	objects.push_back(Salir);
}

EndState::~EndState() {
	objects.clear();
};

void EndState::Update() {
	for (auto i = objects.begin(); i != objects.end(); ++i) {
		(*i).Update();
	}
}

void EndState::Render() const {
	SDL_Rect rect;
	rect.h = 600;
	rect.w = 800;
	rect.x = 0;
	rect.y = 0;
	myGame->devuelveText(6)->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo		
	myTexture->render(screenPos);
	VolverMenu->Render();
	Salir->Render();
	SDL_RenderPresent(myGame->getRenderer());
}

void EndState::HandleEvents() {}
void EndState::Save() {}
