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
//bool save = false;		//variables load y save, usadas para poder conectar dos inputs y guardar en varios archivos distintos.
//bool load = false;
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
			Lista.push_back(nave);
		}
		else if (input1 == 1) {	//Si es 1, es un alien
			lector >> input1;	//Pilla la posición
			lector >> input2;
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al Alien
			lector >> input2;
			if (input2 == 0) {
				Lista.push_back(new ShooterAlien(xd, myGame->devuelveText(2), input2, this, minAlt - myGame->devuelveText(2)->getFrameHeight(), myMothership));
			}
			else {
				Lista.push_back(new Alien(xd, myGame->devuelveText(2), input2, this, minAlt - myGame->devuelveText(2)->getFrameHeight(), myMothership)); //Crea un alie);	//le añade al vector de aliens
			}
		}
		else if (input1 == 5) {	//Si es un 5, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al UFO
			lector >> input2;
			lector >> input1;	//Pilla número de vidas
			lector >> minAlt;	//Pilla número de vidas
			Lista.push_back(new UFO(xd, myGame->devuelveText(5), this, input2, input1, minAlt));//Pilla número de vidas

		}
		else if (input1 == 4) {	//Si es un 4, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker			
			lector >> input2;	//Pilla número de vidas
			Lista.push_back(new Bunker(xd, *myGame->devuelveText(1), this, input2));	//Lo añade al vector de bunkers			
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
PlayState::PlayState(Game* a) :GameState(a){}
PlayState::~PlayState(){

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
void PlayState::fireLaser(Laser* a) {	//Método que añade un nuevo láser al vector de láseres
	Lista.push_back(a);
	a->setListIterator(--Lista.end());
}
void PlayState::EndGame() {	//Método para acabar con el juego
	exit = false;
}