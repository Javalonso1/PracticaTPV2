#include "checkML.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "Button.h"
#include "Game.h"
#include "PlayState.h"

const int MaxH = 600;
const int MaxW = 800;

const int newW = 250;
const int newH = 135;
const int loadW = 230;
const int loadH = 200;
const int exitW = 350;
const int exitH = 265;

const int mainTexIndx = 6;
const int newTexIndx = 7;
const int loadTexIndx = 8;
const int exitTexIndx = 9;

MainMenuState::MainMenuState(Game* e) : GameState(e) {	
	NuevaPartida = new Button(this, myGame->devuelveText(newTexIndx), newW, newH);	
	addEventListener(NuevaPartida);
	NuevaPartida->Connect([this]() {
		PlayState* playstate = new PlayState(myGame);
		myGame->pushState(playstate);
		playstate->LeerArchivo(myGame->GetMap());
		});
	objects.push_back(NuevaPartida);

	CargarPartida = new Button(this, myGame->devuelveText(loadTexIndx), loadW, loadH);
	addEventListener(CargarPartida);
	CargarPartida->Connect([this]() {
		std::string cargar = "saved.txt";		
		PlayState* playstate = new PlayState(myGame);
		myGame->pushState(playstate);
		playstate->LeerArchivo(cargar);
		});
	objects.push_back(CargarPartida);

	Salir = new Button(this, myGame->devuelveText(exitTexIndx), exitW, exitH);
	addEventListener(Salir);
	Salir->Connect([this]() {myGame->ExitGame(); });
	objects.push_back(Salir);
}

MainMenuState::~MainMenuState() {
	objects.clear();
}

void MainMenuState::Save() {}

void MainMenuState::Update() {
	for (auto i = objects.begin(); i != objects.end(); ++i) {
		(*i).Update();
	}
}

void MainMenuState::Render() const {		
	SDL_Rect rect;
	rect.h = MaxH;
	rect.w = MaxW;
	rect.x = 0;
	rect.y = 0;
	myGame->devuelveText(mainTexIndx)->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo
	NuevaPartida->Render();
	CargarPartida->Render();
	Salir->Render();
	SDL_RenderPresent(myGame->getRenderer());
}