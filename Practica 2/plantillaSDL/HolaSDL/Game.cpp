#include "checkML.h"
#include "Game.h"
#include "PlayState.h"
#include "SDL_image.h"
#include <vector>
#include "Alien.h"
#include "Laser.h"
#include "Bunker.h"
#include "Cannon.h"
#include "texture.h"
#include "ShooterAlien.h"
#include <random>
#include <iostream>
#include <fstream>
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"
#include <string>

const int NumDedAliens = 7;	//Constante que indica la cantidad de aliens que tienen que morir para que aumenten su velocidad de movimiento
constexpr int winWidth = 800;
constexpr int winHeight = 600;


Game::Game() : direction(),WinHeight(), WinLong(), renderer(), window(), texturas(), mapa(){}
Game::Game(std::string e) : direction(true), WinHeight(), WinLong(), renderer(),
			window(), texturas(), mapa(e) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		std::string ayo = SDL_GetError();
		throw SDLError(ayo);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		try {
			loadTextures();
		}
		catch (...) {	//Si salta error es que no se han encontrado las texturas
			throw std::string("No se han encontrado las texturas");
		}
		myPlayState = new PlayState(this);
		try { myPlayState->LeerArchivo(mapa);  }	//Intenta leer el archivo de mapa
		catch (InvadersError e) {	//Si salta error es	que no existe un mapa con ese nombre
			throw e;
		}
		myPlayState->Run();
	}


}
Game::~Game() {	//Destructor del Game	
	for (int i = 0; i < NUM_TEXTURES; i++) {	//Se borran todas las texturas
		delete(texturas[i]);
	}
	//delete(myMothership);	
	SDL_DestroyRenderer(renderer);	//Se destruye el renderer
	SDL_DestroyWindow(window);	//Se destruye la ventana
	SDL_Quit();	//Se sale de SDL	
	/*for (auto i : Lista) {
		delete i;
	}
	Lista.clear();*/
}


void Game::loadTextures() {
	texturas[0] = new Texture(renderer, "spaceship.png", 1, 1);	//Inicializa las texturas
	texturas[2] = new Texture(renderer, "aliens.png", 3, 2);
	texturas[1] = new Texture(renderer, "bunker.png", 1, 4);
	texturas[3] = new Texture(renderer, "stars.png", 1, 1);
	texturas[4] = new Texture(renderer, "laser.png", 1, 1);
	texturas[5] = new Texture(renderer, "ufo.png", 1, 2);
}

SDL_Renderer* Game::getRenderer() {
	return renderer;
}
Texture* Game::devuelveText(int i) {
		return texturas[i];
	}