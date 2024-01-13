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
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "EndState.h"

const int NumDedAliens = 7;	//Constante que indica la cantidad de aliens que tienen que morir para que aumenten su velocidad de movimiento
constexpr int winWidth = 800;
constexpr int winHeight = 600;

const int cannTexIndx = 0;
const int bunkTexIdx = 1;
const int alienTexIndx = 2;
const int backTexIndx = 3;
const int laserTexIndx = 4;
const int ufoTexIndx = 5;
const int mainTexIndx = 6;
const int newTexIndx = 7;
const int loadTexIndx = 8;
const int exitTexIndx = 9;
const int contTexIndx = 10;
const int saveTexIndx = 11;
const int retTexIndx = 12;
const int winTexIndx = 13;
const int loseTexIndx = 14;
const int bomTexIndx = 15;
const int protTexIndx = 16;
const int shiTexIndx = 17;

Game::Game() : WinHeight(), WinLong(), renderer(), window(), texturas(), mapa(){}
Game::Game(std::string e) : WinHeight(), WinLong(), renderer(),
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
		DeusEx = new GameStateMachine();		
		DeusEx->pushState(new MainMenuState(this));						
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
	delete DeusEx;
}


void Game::loadTextures() {
	texturas[cannTexIndx] = new Texture(renderer, "spaceship.png", 1, 1);	//Inicializa las texturas
	texturas[alienTexIndx] = new Texture(renderer, "aliens.png", 3, 2);
	texturas[bunkTexIdx] = new Texture(renderer, "bunker.png", 1, 4);
	texturas[backTexIndx] = new Texture(renderer, "stars.png", 1, 1);
	texturas[laserTexIndx] = new Texture(renderer, "laser.png", 1, 1);
	texturas[ufoTexIndx] = new Texture(renderer, "ufo.png", 1, 2);
	texturas[mainTexIndx] = new Texture(renderer, "mainMenu.png", 1, 1);
	texturas[newTexIndx] = new Texture(renderer, "nuevaPartida.png", 1, 1);
	texturas[loadTexIndx] = new Texture(renderer, "cargarPartida.png", 1, 1);
	texturas[exitTexIndx] = new Texture(renderer, "salir.png", 1, 1);
	texturas[contTexIndx] = new Texture(renderer, "continuar.png", 1, 1);
	texturas[saveTexIndx] = new Texture(renderer, "guardarPartida.png", 1, 1);
	texturas[retTexIndx] = new Texture(renderer, "volverAlMenu.png", 1, 1);	
	texturas[winTexIndx] = new Texture(renderer, "hasGanado.png", 1, 1);
	texturas[loseTexIndx] = new Texture(renderer, "gameOver.png", 1, 1);
	texturas[bomTexIndx] = new Texture(renderer, "bomb.png", 1, 1);
	texturas[protTexIndx] = new Texture(renderer, "shield.png", 1, 1);
	texturas[shiTexIndx] = new Texture(renderer, "shield_reward.png", 1, 1);
}

SDL_Renderer* const Game::getRenderer() {
	return renderer;
}

Texture* Game::devuelveText(int i) const {
		return texturas[i];
}

void Game::ExitGame() {
	exit = true;
}

void Game::Run() {	
	while (!exit) {
		while (SDL_PollEvent(&manolo)) {
			DeusEx->handleEvent(manolo);
		}
		DeusEx->update();
		DeusEx->render();		
		SDL_Delay(20);
		if (goback) {
			popState();
			goback = false;
			if (guardado) {
				DeusEx->Save();
				pushState(new PauseState(this));
			}
		}
		if (pause) {
			pushState(new PauseState(this));
			pause = false;
		}
	}
	//Borrar el juego
}
void Game::continuar(bool aux) {
	goback = true;
	guardado = aux;
}
void Game::PauseGame() {
	pause = true;
}
void Game::pushState(GameState* newState) {
	DeusEx->pushState(newState);
}

void Game::popState() {
	DeusEx->popState();
}

void Game::replaceState(GameState* newState) {
	DeusEx->replaceState(newState);
}

std::string Game::GetMap() const{
	return mapa;
}
void Game::EndGame(bool a) {
	pushState(new EndState(this, a));
}