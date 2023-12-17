#include "checkML.h"
#include "PauseState.h"
#include "GameState.h"
#include "Button.h"
#include "Game.h"

PauseState::PauseState(Game* e) : GameState(e) {
	Continuar = new Button(this, myGame->devuelveText(10), 290, 115);
	GuardarPartida = new Button(this, myGame->devuelveText(11), 220, 155);
	CargarPartida = new Button(this, myGame->devuelveText(8), 230, 195); //Creo que podríamos dejar la carga solo para el main menu para ahorrarnos trabajo
	VolverMenu = new Button(this, myGame->devuelveText(12), 230, 235);	
}

PauseState::~PauseState() {}

void PauseState::Update() {

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
	CargarPartida->Render();
	VolverMenu->Render();
	SDL_RenderPresent(myGame->getRenderer());
}

void PauseState::HandleEvents() {}
