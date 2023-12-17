#include "checkML.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "Button.h"
#include "Game.h"

MainMenuState::MainMenuState(Game* e) : GameState(e) {	
	NuevaPartida = new Button(this, myGame->devuelveText(7), 250, 135);	
	CargarPartida = new Button(this, myGame->devuelveText(8), 230, 200);	
	Salir = new Button(this, myGame->devuelveText(9), 350, 265);
}

MainMenuState::~MainMenuState() {}

void MainMenuState::Update() {

}

void MainMenuState::Render() const {		
	SDL_Rect rect;
	rect.h = 600;
	rect.w = 800;
	rect.x = 0;
	rect.y = 0;
	myGame->devuelveText(6)->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo
	NuevaPartida->Render();
	CargarPartida->Render();
	Salir->Render();
	SDL_RenderPresent(myGame->getRenderer());
}

void MainMenuState::HandleEvents() {

}