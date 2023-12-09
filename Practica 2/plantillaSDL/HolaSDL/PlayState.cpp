#include "PlayState.h"
#include "Game.h"
#include "GameState.h"
#include "Alien.h"
#include "ShooterAlien.h"
#include "Bunker.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include "Cannon.h"
#include "Laser.h"
#include "UFO.h"
#include <iostream>
#include <fstream>
#include <string>
#include "FileFormatError.h"
#include "FileNotFoundError.h"
bool save = false;		//variables load y save, usadas para poder conectar dos inputs y guardar en varios archivos distintos.
bool load = false;
bool direction = false;


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
			nave = new Cannon(ab, myGame->returnTexture(0), this, input1, input2);	//Crea una nave nueva
			Lista.push_back(nave);
		}
		else if (input1 == 1) {	//Si es 1, es un alien
			lector >> input1;	//Pilla la posición
			lector >> input2;
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al Alien
			lector >> input2;
			if (input2 == 0) {
				Lista.push_back(new ShooterAlien(xd, myGame->returnTexture(2), input2, this, minAlt - myGame->returnTexture(2)->getFrameHeight(), myMothership));
			}
			else {
				Lista.push_back(new Alien(xd, myGame->returnTexture(2), input2, this, minAlt - myGame->returnTexture(2)->getFrameHeight(), myMothership)); //Crea un alie);	//le añade al vector de aliens
			}
		}
		else if (input1 == 5) {	//Si es un 5, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al UFO
			lector >> input2;
			lector >> input1;	//Pilla número de vidas
			lector >> minAlt;	//Pilla número de vidas
			Lista.push_back(new UFO(xd, myGame->returnTexture(5), this, input2, input1, minAlt));//Pilla número de vidas

		}
		else if (input1 == 4) {	//Si es un 4, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker			
			lector >> input2;	//Pilla número de vidas
			Lista.push_back(new Bunker(xd, *(myGame->returnTexture(1)), this, input2));	//Lo añade al vector de bunkers			
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
PlayState::PlayState(std::string a, Game*b): Lista(), aDestruir(), nave(), myGame(b){}
PlayState::~PlayState() {

}



void PlayState::HandleEvents() {	//Método que pilla un input del jugador y se lo pasa a la nave
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
int PlayState::GetDirection() {	//Método que los aliens usan para ver si se mueven a la izquierda o derecha
	if (direction) return 1;
	else
	{
		return -1;
	}
}
void PlayState::fireLaser(Laser* a) {	//Método que añade un nuevo láser al vector de láseres
	Lista.push_back(a);
	a->setListIterator(--Lista.end());
}
bool PlayState::CheckColisions(SDL_Rect* LaserRect, bool friendly) {	//método que comprueba la colisiones del láser	
	std::list<SceneObject*>::iterator i = Lista.begin();
	while (i != Lista.end() && !(*i)->hit(LaserRect, friendly)) {
		i++;
	}
	return i != Lista.end();
}
void PlayState::HasDied(std::list<SceneObject*>::iterator it) {
	aDestruir.push_back(it);
}
void PlayState::DestroyDead() {
	for (std::list <std::list<SceneObject*>::iterator>::iterator i = aDestruir.begin(); i != aDestruir.end(); i++) {
		delete** i;
		Lista.erase(*i);
	}
	aDestruir.clear();
}
void PlayState::Save(int i) {
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
			LeerArchivo(cargar); //Se carga la nueva información
			load = false;
		}
	}
}