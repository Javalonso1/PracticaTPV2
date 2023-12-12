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
		try { /*LeerArchivo(mapa); */}	//Intenta leer el archivo de mapa
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
void Game::HandleEvents() {	//Método que pilla un input del jugador y se lo pasa a la nave
	SDL_Event ev;
	int move = 0;
	bool shoot = false;
	while (SDL_PollEvent(&ev) != 0) {			//Lector de eventos de teclado. Lee los inputs del jugador y los pasa a variables
		switch (ev.type) {
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) {
			case SDLK_LEFT:
				load = false;
				save = false;
				move = -1;
				break;
			case SDLK_RIGHT:
				load = false;
				save = false;
				move = 1;
				break;
			case SDLK_SPACE:
				load = false;
				save = false;
				shoot = true;
				break;
			case SDLK_g:
				load = false;
				save = true;
				break;
			case SDLK_l:
				save = false;
				load = true;
				break;
			case SDLK_0:
				Save(0);
				break;
			case SDLK_1:
				Save(1);
				break;
			case SDLK_2:
				Save(2);
				break;
			case SDLK_3:
				Save(3);
				break;
			case SDLK_4:
				Save(4);
				break;
			case SDLK_5:
				Save(5);
				break;
			case SDLK_6:
				Save(6);
				break;
			case SDLK_7:
				Save(7);
				break;
			case SDLK_8:
				Save(8);
				break;
			case SDLK_9:
				Save(9);
				break;
			default:
				break;
			}
		}
	}	
	nave->handleEvent(move, shoot);
}
int Game::GetDirection() {	//Método que los aliens usan para ver si se mueven a la izquierda o derecha
	if (direction) return 1;
	else
	{
		return -1;
	}	
}
void Game::fireLaser(Laser* a) {	//Método que añade un nuevo láser al vector de láseres
	Lista.push_back(a);
	a->setListIterator(--Lista.end());
}
bool Game::CheckColisions(SDL_Rect* LaserRect, bool friendly) {	//método que comprueba la colisiones del láser	
	std::list<SceneObject*>::iterator i = Lista.begin();
	while (i != Lista.end() && !(*i)->hit(LaserRect, friendly)) {
		i++;
	}
	return i != Lista.end();
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

void Game::HasDied(std::list<SceneObject*>::iterator it) {
	aDestruir.push_back(it);
}

void Game::DestroyDead() {
	for (std::list <std::list<SceneObject*>::iterator>::iterator i = aDestruir.begin(); i != aDestruir.end(); i++) {
		delete **i;
		Lista.erase(*i);
	}
	aDestruir.clear();
}

void Game::Save(int i) {
	if (save) { //si save es igual a true, es que se quiere guardar partida
		std::string guardar = "saved";
		guardar += std::to_string(i);
		guardar += ".txt";	//Se pilla la dirección
		std::cout << guardar;
		std::ofstream a(guardar);		
		myMothership->save(a);	//Se guarda la mothership, y luego se guardan, de uno en uno, todos los elementos de la lista de objetos
		for (std::list<SceneObject*>::iterator i = Lista.begin(); i != Lista.end(); i++) {
			a << "\n";
			(*i)->save(a);
		}
		save = false;	//Se desactiva save
	}
	else {
		if (load) {	//si load es true, es que se quiere cargar partida
			std::string cargar = "saved";
			cargar += std::to_string(i);
			cargar += ".txt";	//Se pilla la dirección
			Lista.clear();	//se elimina la lista de objetos y se borra la Mothership
			delete(myMothership);
			/*LeerArchivo(cargar); //Se carga la nueva información*/
			load = false;
		}
	}
	
}
Texture* Game::devuelveText(int i) {
		return texturas[i];
	}