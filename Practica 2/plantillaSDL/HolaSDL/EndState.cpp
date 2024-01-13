#include "checkML.h"
#include "EndState.h"
#include "GameState.h"
#include "Button.h"
#include "texture.h"
#include "MainMenuState.h"
#include "Game.h"
const int LogoPosX = 300;
const int LogoPosY = 135;

const int retW = 230;
const int retH = 200;
const int exitW = 350;
const int exitH = 265;

const int screenWidth = 800;
const int screenHeigth = 600;

const int backTexIndx = 3;
const int exitTexIndx = 9;
const int retTexIndx = 12;
const int winTexIndx = 13;
const int loseTexIndx = 14;

EndState::EndState(Game* e, bool a) : GameState(e) {	
	screenPos = SDL_Rect();
	screenPos.x = LogoPosX;
	screenPos.y = LogoPosY;	
	if (a) {
		myTexture = myGame->devuelveText(winTexIndx);
	}
	else {
		myTexture = myGame->devuelveText(loseTexIndx);
	}
	screenPos.h = myTexture->getFrameHeight();
	screenPos.w = myTexture->getFrameWidth();

	VolverMenu = new Button(this, myGame->devuelveText(retTexIndx), retW, retH);
	addEventListener(VolverMenu);
	VolverMenu->Connect([this]() {
		MainMenuState* playstate = new MainMenuState(myGame);
		myGame->pushState(playstate);
		});
	objects.push_back(VolverMenu);
	Salir = new Button(this, myGame->devuelveText(exitTexIndx), exitW, exitH);
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
	rect.h = screenHeigth;
	rect.w = screenWidth;
	rect.x = 0;
	rect.y = 0;
	myGame->devuelveText(backTexIndx)->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo		
	myTexture->render(screenPos);
	VolverMenu->Render();
	Salir->Render();
	SDL_RenderPresent(myGame->getRenderer());
}

void EndState::HandleEvents() {}
void EndState::Save() {}
