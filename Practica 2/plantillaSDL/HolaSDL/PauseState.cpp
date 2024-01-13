#include "checkML.h"
#include "PauseState.h"
#include "GameState.h"
#include "Button.h"
#include "MainMenuState.h"
#include "Game.h"

const int screedWidth = 800;
const int screedHeigth = 600;

const int contW = 290;
const int contH = 135;
const int saveW = 220;
const int saveH = 200;
const int retW = 230;
const int retH = 265;

const int backTexIndx = 3;
const int contTexIndx = 10;
const int saveTexIndx = 11;
const int retTexIndx = 12;

PauseState::PauseState(Game* e) : GameState(e) {
	Continuar = new Button(this, myGame->devuelveText(contTexIndx), contW, contH);
	addEventListener(Continuar);
	Continuar->Connect([this]() {
		myGame->continuar(false);
		});
	objects.push_back(Continuar);
	GuardarPartida = new Button(this, myGame->devuelveText(saveTexIndx), saveW, saveH);
	addEventListener(GuardarPartida);
	GuardarPartida->Connect([this]() {
		myGame->continuar(true);
		});
	objects.push_back(GuardarPartida);
	VolverMenu = new Button(this, myGame->devuelveText(retTexIndx), retW, retH);
	addEventListener(VolverMenu);
	VolverMenu->Connect([this]() {		
		MainMenuState* playstate = new MainMenuState(myGame);
		myGame->pushState(playstate);		
		});
	objects.push_back(VolverMenu);
}

PauseState::~PauseState() {
	objects.clear();
}

void PauseState::Update() {
	for (auto i = objects.begin(); i != objects.end(); ++i) {
		(*i).Update();
	}
}

void PauseState::Render() const {
	SDL_Rect rect;
	rect.h = screedHeigth;
	rect.w = screedWidth;
	rect.x = 0;
	rect.y = 0;
	myGame->devuelveText(backTexIndx)->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo
	Continuar->Render();
	GuardarPartida->Render();	
	VolverMenu->Render();
	SDL_RenderPresent(myGame->getRenderer());
}

void PauseState::HandleEvents() {}
void PauseState::Save() {}
