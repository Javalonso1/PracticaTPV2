#include "checkML.h"
#include "PlayState.h"
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

//const int NumDedAliens = 7;	//Constante que indica la cantidad de aliens que tienen que morir para que aumenten su velocidad de movimiento
//constexpr int winWidth = 800;
//constexpr int winHeight = 600;
bool save = false;		//variables load y save, usadas para poder conectar dos inputs y guardar en varios archivos distintos.
bool load = false;
void PlayState::LeerArchivo(std::string e) {		//Método para leer archivos y transformarlos en mapas
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
			nave = new Cannon(ab, myGame->devuelveText(0), this, input1, input2);	//Crea una nave nueva
			pasta.push_back(nave);
		}
		else if (input1 == 1) {	//Si es 1, es un alien
			lector >> input1;	//Pilla la posición
			lector >> input2;
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al Alien
			lector >> input2;
			if (input2 == 0) {
				pasta.push_back(new ShooterAlien(xd, myGame->devuelveText(2), input2, this, minAlt - myGame->devuelveText(2)->getFrameHeight(), myMothership));
			}
			else {
				pasta.push_back(new Alien(xd, myGame->devuelveText(2), input2, this, minAlt - myGame->devuelveText(2)->getFrameHeight(), myMothership)); //Crea un alie);	//le añade al vector de aliens
			}
		}
		else if (input1 == 5) {	//Si es un 5, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al UFO
			lector >> input2;
			lector >> input1;	//Pilla número de vidas
			lector >> minAlt;	//Pilla número de vidas
			pasta.push_back(new UFO(xd, myGame->devuelveText(5), this, input2, input1, minAlt));//Pilla número de vidas

		}
		else if (input1 == 4) {	//Si es un 4, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker			
			lector >> input2;	//Pilla número de vidas
			pasta.push_back(new Bunker(xd, *myGame->devuelveText(1), this, input2));	//Lo añade al vector de bunkers			
		}
		else if (input1 == 6) {
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker			
			lector >> input1;	//Pilla número de vidas
			lector >> input2;	//Pilla número de vidas
			pasta.push_back(new Laser(xd, input1, input2, this));	//Crea el láser
		}
		else if (input1 == 3) {
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

}
PlayState::PlayState(Game* a) :GameState(a), exit(true) {}
PlayState::~PlayState(){

}

void PlayState::Run() {
	while (exit) {								//Bucle principal del juego. Mientras el método "getExit" del game de true, el juego no habrá acabado
		Update();					//Ejecuta todos los eventos del main (Render, Update...)
		Render();
		HandleEvents();
		SDL_Delay(5);				//Pequeño delay
	}
}

void PlayState::Render() const {
	SDL_Rect rect;
	rect.h = 600;
	rect.w = 800;
	rect.x = 0;
	rect.y = 0;
	myGame->devuelveText(3)->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo
	for (auto i = pasta.begin(); i != pasta.end(); ++i) {
		(*i).Render();
	}
	SDL_RenderPresent(myGame->getRenderer());
}

void PlayState::Update() {
	auto i = pasta.begin();
	while (i != pasta.end()) {
		(*i).Update();
		++i;
	}
	myMothership->Update();
	if (myMothership->getAlienCount() <= 0) {
		exit = false;
	}
	DestroyDead();
}
void PlayState::HandleEvents() {
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
			case SDLK_ESCAPE:
				std::cout << "AAA";
				break;			
			default:
				break;
			}
		}
	}
}

bool PlayState::CheckColisions(SDL_Rect* LaserRect, bool friendly) {	//método que comprueba la colisiones del láser	
	auto i = pasta.begin();
	while (i != pasta.end() && !(*i).hit(LaserRect, friendly)) {
		++i;
	}
	return i != pasta.end();
}
void PlayState::HasDied(GameList<SceneObject>::anchor it) {
	aDestruir.push_back(it);
}
void PlayState::fireLaser(Laser* a) {	//Método que añade un nuevo láser al vector de láseres
	pasta.push_back(a);
}
void PlayState::EndGame() {	//Método para acabar con el juego
	exit = false;
}
void PlayState::DestroyDead() {
	for (auto i = aDestruir.begin(); i != aDestruir.end(); i++) {
		pasta.erase(*i);
	}
	aDestruir.clear();
	for (auto i = queso.begin(); i != queso.end(); i++) {
		pizza.erase(*i);
	}
	queso.clear();
}
void PlayState::Save(int i) {
	if (save) { //si save es igual a true, es que se quiere guardar partida
		std::string guardar = "saved";
		guardar += std::to_string(i);
		guardar += ".txt";	//Se pilla la dirección
		std::cout << guardar;
		std::ofstream a(guardar);
		myMothership->save(a);	//Se guarda la mothership, y luego se guardan, de uno en uno, todos los elementos de la lista de objetos
		for (auto i = pasta.begin(); i != pasta.end(); ++i) {
			a << "\n";
			(*i).save(a);
		}
		save = false;	//Se desactiva save
	}
	else {
		if (load) {	//si load es true, es que se quiere cargar partida
			std::string cargar = "saved";
			cargar += std::to_string(i);
			cargar += ".txt";	//Se pilla la dirección
			pasta.clear();	//se elimina la lista de objetos y se borra la Mothership
			delete(myMothership);
			LeerArchivo(cargar); //Se carga la nueva información*/
			load = false;
		}
	}
}