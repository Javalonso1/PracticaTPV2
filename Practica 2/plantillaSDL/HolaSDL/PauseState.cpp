#include "checkML.h"
#include "PauseState.h"
#include "GameState.h"
#include "Button.h"
#include "MainMenuState.h"
#include "Game.h"

PauseState::PauseState(Game* e) : GameState(e) {
	Continuar = new Button(this, myGame->devuelveText(10), 290, 135);
	addEventListener(Continuar);
	Continuar->Connect([this]() {
		myGame->continuar(false);
		});
	pizza.push_back(Continuar);
	GuardarPartida = new Button(this, myGame->devuelveText(11), 220, 200);
	addEventListener(GuardarPartida);
	GuardarPartida->Connect([this]() {
		myGame->continuar(true);
		});
	pizza.push_back(GuardarPartida);	
	VolverMenu = new Button(this, myGame->devuelveText(12), 230, 265);	
	addEventListener(VolverMenu);
	VolverMenu->Connect([this]() {		
		MainMenuState* playstate = new MainMenuState(myGame);
		myGame->pushState(playstate);		
		});
	pizza.push_back(VolverMenu);
}

PauseState::~PauseState() {}

void PauseState::Update() {
	for (auto i = pizza.begin(); i != pizza.end(); ++i) {
		(*i).Update();
	}
}

void PauseState::Render() const {
	SDL_Rect rect;
	rect.h = 600;
	rect.w = 800;
	rect.x = 0;
	rect.y = 0;
	myGame->devuelveText(6)->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo
	Continuar->Render();
	GuardarPartida->Render();	
	VolverMenu->Render();
	SDL_RenderPresent(myGame->getRenderer());
}

void PauseState::HandleEvents() {}
void PauseState::Save() {}
