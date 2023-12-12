#include "checkML.h"
#include "Game.h"
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
bool save = false;		//variables load y save, usadas para poder conectar dos inputs y guardar en varios archivos distintos.
bool load = false;

Game::Game() : direction(),WinHeight(), WinLong(), renderer(), window(), exit(), texturas(), dedAliens(0), mapa(){}
Game::Game(std::string e) : direction(true), WinHeight(), WinLong(), renderer(),
			window(), exit(true), texturas(), dedAliens(0), mapa(e), rnd(time(nullptr)) {}
Game::~Game() {	//Destructor del Game	
	for (int i = 0; i < NUM_TEXTURES; i++) {	//Se borran todas las texturas
		delete(texturas[i]);
	}
	delete(myMothership);	
	SDL_DestroyRenderer(renderer);	//Se destruye el renderer
	SDL_DestroyWindow(window);	//Se destruye la ventana
	SDL_Quit();	//Se sale de SDL	
	for (auto i : Lista) {
		delete i;
	}
	Lista.clear();
}


void Game::loadTextures() {
	texturas[0] = new Texture(renderer, "spaceship.png", 1, 1);	//Inicializa las texturas
	texturas[2] = new Texture(renderer, "aliens.png", 3, 2);
	texturas[1] = new Texture(renderer, "bunker.png", 1, 4);
	texturas[3] = new Texture(renderer, "stars.png", 1, 1);
	texturas[4] = new Texture(renderer, "laser.png", 1, 1);
	texturas[5] = new Texture(renderer, "ufo.png", 1, 2);
}
Texture* Game::returnTexture(int i) {
	return texturas[i];
}

void Game::Run() {	//Método al que se llama para ejecutar un tick en el juego
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
		try { LeerArchivo(mapa); }	//Intenta leer el archivo de mapa
		catch (InvadersError e) {	//Si salta error es	que no existe un mapa con ese nombre
			throw e;
		}

		while (exit) {								//Bucle principal del juego. Mientras el método "getExit" del game de true, el juego no habrá acabado
			Render();
			Update();					//Ejecuta todos los eventos del main (Render, Update...)
			SDL_Delay(5);				//Pequeño delay
			HandleEvents();
		}
	}
}

void Game::Render() {//Método que renderiza el juego	
	SDL_Rect rect;	
	rect.h = 600;
	rect.w = 800;
	rect.x = 0;
	rect.y = 0;
	texturas[3]->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo
	for (std::list<SceneObject*>::iterator i = Lista.begin(); i != Lista.end(); i++) {
		(*i)->Render();
	}
	SDL_RenderPresent(renderer);
}



void Game::Update() {	//Método que llama a todos los updates del juego		
	system("cls");
	std::list<SceneObject*>::iterator i = Lista.begin();
	while (i != Lista.end()) {
		(*i)->Update();
		i++;
	}	
	myMothership->Update();
	if (myMothership->getAlienCount() <= 0) {
		exit = false;
	}
	std::cout << myMothership->getPoint();
 	DestroyDead();
}

int Game::getRandomRange(int min, int max) {	//Método que pilla un número random	
	return std::uniform_int_distribution<int>(min, max)(rnd);	
}

void Game::EndGame() {	//Método para acabar con el juego
	exit = false;
}

bool Game::getExit() {	//Método que comprueba si ha acabado el juego
	return exit;
}

SDL_Renderer* Game::getRenderer() {
	return renderer;
}
