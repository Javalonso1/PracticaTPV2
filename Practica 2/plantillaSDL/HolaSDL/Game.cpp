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
bool save = false;
bool load = false;

void Game::LeerArchivo(std::string e) {		//Método para leer archivos y transformarlos en mapas
	std::ifstream lector(e);
	int lineas = 0;
	int minAlt;
	if (lector.peek() == EOF) throw FileNotFoundError(e);	//Si no hay archivo nada más empezar, eso es que el nombre de mapa es incorrecto, por lo que se lanza un error
	while (lector.peek() != EOF) {			//Mientras no se haya leído hasta el final del archivo...
		int input1;
		int input2;
		lector >> input1;		//se lee el tipo de archivo a crear
		if (input1 == 0) {		//si es 0, eso es que es una nave
			lector >> input1;	//Pilla la posición
			lector >> minAlt;	
			Point2D<int> ab(input1, minAlt); //Crea un Point2D que darle a la nave
			lector >> input1;	
			lector >> input2;
			nave = new Cannon(ab, texturas[0], this,input1, input2);	//Crea una nave nueva
			Lista.push_back(nave);
		}
		else if (input1 == 1) {	//Si es 1, es un alien
			lector >> input1;	//Pilla la posición
			lector >> input2;	
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al Alien
			lector >> input2;			
			if (input2 == 0) {
				Lista.push_back(new ShooterAlien(xd, texturas[2], input2, this, minAlt - texturas[0]->getFrameHeight(), myMothership));
			}
			else {
				Lista.push_back(new Alien(xd, texturas[2], input2, this, minAlt - texturas[0]->getFrameHeight(), myMothership)); //Crea un alie);	//le añade al vector de aliens
			}
		}
		else if (input1 == 5) {	//Si es un 5, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al UFO
			lector >> input2;
			lector >> input1;	//Pilla número de vidas
			lector >> minAlt;	//Pilla número de vidas
			Lista.push_back(new UFO(xd, texturas[5], this, input2, input1, minAlt));//Pilla número de vidas
			
		}
		else if (input1 == 4) {	//Si es un 4, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker			
			lector >> input2;	//Pilla número de vidas
			Lista.push_back(new Bunker(xd, *texturas[1], this, input2));	//Lo añade al vector de bunkers			
		}		
		else if (input1 == 6) {
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker			
			lector >> input1;	//Pilla número de vidas
			lector >> input2;	//Pilla número de vidas
			Lista.push_back(new Laser(xd, input1, input2, this));	//Crea el láser
		}
		else if (input1 == 3) {
			//a << "3 " << direction << " " << level << " " << frames;
			lector >> input1;
			lector >> input2;
			lector >> minAlt;
			myMothership = new Mothership(this, input1, input2, minAlt);			
		}
		else {
			throw FileFormatError("not valid object type", lineas, e);
		}
		lineas++;
	}	
	for (std::list<SceneObject*>::iterator i = Lista.begin(); i != Lista.end(); i++) {
		(*i)->setListIterator(i);
	}
}
Game::Game() : direction(),WinHeight(), WinLong(), renderer(), window(), exit(), texturas(), dedAliens(0), mapa(){}
Game::Game(std::string e) : direction(true), WinHeight(), WinLong(), renderer(),
			window(), exit(true), texturas(), Change(false), dedAliens(0), mapa(e), rnd(time(nullptr)) {}
Game::~Game() {	//Destructor del Game
	//delete(nave);	//Se borra la nave
	for (int i = 0; i < NUM_TEXTURES; i++) {	//Se borran todas las texturas
		delete(texturas[i]);
	}
	delete(myMothership);
	//delete(ufo);
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
		try { LeerArchivo(mapa); }	//Intenta leer el archivo de mapa
		catch (InvadersError e) {	//Si salta error es	que no existe un mapa con ese nombre
			throw e;
		}

		while (exit) {								//Bucle principal del juego. Mientras el método "getExit" del game de true, el juego no habrá acabado								
			if (Change) {	//Si la variable Change es true, eso es que los aliens han llegado a una pared				
				Change = false;	//Se desactiva change
				/*for (int i = 0; i < aliens.size(); i++) {	//Se mueve a los aliens hacia abajo
					aliens[i].VerticalMove(veticalDown);
				}*/
			}
			Render();
			Update();					//Ejecuta todos los eventos del main (Render, Update...)
			SDL_Delay(25);				//Pequeño delay
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
		/*else
		{
			HasDied(i);			
			i = Lista.end();
		}		*/		
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
bool Game::cannotMove() {	//Método al que llaman los aliens de chocar con una pared
	Change = true;
	return true;
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
	if (save) {
		std::string guardar = "saved";
		guardar += std::to_string(i);
		guardar += ".txt";
		std::cout << guardar;
		std::ofstream a(guardar);		
		myMothership->save(a);
		for (std::list<SceneObject*>::iterator i = Lista.begin(); i != Lista.end(); i++) {
			a << "\n";
			(*i)->save(a);
		}		
	}
	else {
		if (load) {
			std::string cargar = "saved";
			cargar += std::to_string(i);
			cargar += ".txt";
			//std::list<SceneObject*> Lista2;
			//Lista = Lista2;
			Lista.clear();
			LeerArchivo(cargar);			
		}
	}
}