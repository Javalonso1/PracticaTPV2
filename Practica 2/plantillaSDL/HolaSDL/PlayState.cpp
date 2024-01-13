#include "checkML.h"
#include "PlayState.h"
#include "Game.h"
#include "SDL_image.h"
#include <vector>
#include "Alien.h"
#include "Laser.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Bomba.h"
#include "Escudo.h"
#include "texture.h"
#include "ShooterAlien.h"
#include <random>
#include <iostream>
#include <fstream>
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"
#include "PauseState.h"
#include <string>

const int screenWidth = 800;
const int screenHeigth = 600;

const int cannIndx = 0;
const int alienIndx = 1;
const int bunkIndx = 4;
const int mothIndx = 3;
const int ufoIndx = 5;
const int laserIndx = 6;
const int bomIndx = 7;
const int shiIndx = 8;

const int cannTexIndx = 0;
const int bunkTexIdx = 1;
const int alienTexIndx = 2;
const int backTexIndx = 3;
const int ufoTexIndx = 5;
const int bomTexIndx = 15;
const int protTexIndx = 16; 
const int shiTexIndx = 17;

void PlayState::LeerArchivo(std::string e) {		//Método para leer archivos y transformarlos en mapas
	std::ifstream lector(e);
	int lineas = 0;
	int minAlt;
	if (lector.peek() == EOF) throw FileNotFoundError(e);	//Si no hay archivo nada más empezar, eso es que el nombre de mapa es incorrecto, por lo que se lanza un error
	while (lector.peek() != EOF) {			//Mientras no se haya leído hasta el final del archivo...
		int input1;
		int input2;
		lector >> input1;		//se lee el tipo de archivo a crear
		if (input1 == cannIndx) {		//si es 0, eso es que es una nave
			lector >> input1;	//Pilla la posición
			lector >> minAlt;
			Point2D<int> ab(input1, minAlt); //Crea un Point2D que darle a la nave
			lector >> input1;
			lector >> input2;
			nave = new Cannon(ab, myGame->devuelveText(cannTexIndx), this, input1, input2, myGame->devuelveText(protTexIndx));	//Crea una nave nueva
			scnobj.push_back(nave);
			objects.push_back(nave);
		}
		else if (input1 == alienIndx) {	//Si es 1, es un alien
			lector >> input1;	//Pilla la posición
			lector >> input2;
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al Alien
			lector >> input2;
			if (input2 == 0) {
				ShooterAlien* alien = new ShooterAlien(xd, myGame->devuelveText(alienTexIndx), input2, this, minAlt - myGame->devuelveText(alienTexIndx)->getFrameHeight(), myMothership);
				scnobj.push_back(alien);
				objects.push_back(alien);
			}
			else {
				Alien* alien = new Alien(xd, myGame->devuelveText(alienTexIndx), input2, this, minAlt - myGame->devuelveText(alienTexIndx)->getFrameHeight(), myMothership);
				scnobj.push_back(alien); //Crea un alien
				objects.push_back(alien);
			}
		}
		else if (input1 == ufoIndx) {	//Si es un 5, es un UFO
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al UFO
			lector >> input2;
			lector >> input1;	
			lector >> minAlt;	
			UFO* uf = new UFO(xd, myGame->devuelveText(ufoTexIndx), this, input2, input1, minAlt);
			scnobj.push_back(uf);
			objects.push_back(uf);
		}
		else if (input1 == bunkIndx) {	//Si es un 4, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker			
			lector >> input2;	//Pilla número de vidas
			Bunker* bunk = new Bunker(xd, *myGame->devuelveText(bunkTexIdx), this, input2);
			scnobj.push_back(bunk);	//Lo añade al vector de bunkers		
			objects.push_back(bunk);
		}
		else if (input1 == laserIndx) {
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker			
			lector >> input1;	//Pilla número de vidas
			lector >> input2;	//Pilla número de vidas
			Laser* las = new Laser(xd, input1, input2, this);
			scnobj.push_back(las);	//Crea el láser
			objects.push_back(las);
		}
		else if (input1 == bomIndx) {
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle a la bomba
			Bomba* bom = new Bomba(xd, myGame->devuelveText(bomTexIndx), this);
			scnobj.push_back(bom);
			objects.push_back(bom);
		}
		else if (input1 == shiIndx) {
			lector >> input1;
			lector >> input2;	//Pilla la posición
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al escudo
			Escudo* esc = new Escudo(xd, myGame->devuelveText(shiTexIndx), this);
			scnobj.push_back(esc);
			objects.push_back(esc);
		}
		else if (input1 == mothIndx) {
			lector >> input1;
			lector >> input2;
			lector >> minAlt;
			myMothership = new Mothership(this, input1, input2, minAlt);
			objects.push_back(myMothership);
		}
		else {
			throw FileFormatError("not valid object type", lineas, e);
		}
		lineas++;
	}

}

PlayState::PlayState(Game* a) :GameState(a) {}

PlayState::~PlayState(){
	objects.clear();
}

void PlayState::Render() const {
	SDL_Rect rect;
	rect.h = screenHeigth;
	rect.w = screenWidth;
	rect.x = 0;
	rect.y = 0;
	myGame->devuelveText(backTexIndx)->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo
	for (auto i = scnobj.begin(); i != scnobj.end(); ++i) {
		(*i).Render();
	}
	SDL_RenderPresent(myGame->getRenderer());
}

void PlayState::Update() {
	auto i = scnobj.begin();
	while (i != scnobj.end()) {
		(*i).Update();
		++i;
	}
	myMothership->Update();
	if (myMothership->getAlienCount() <= 0) {
		EndGame(true);
	}
	DestroyDead();
}
void PlayState::HandleEvents(const SDL_Event& ev) {
	switch (ev.type) {
	case SDL_KEYDOWN:
		switch (ev.key.keysym.sym) {
		case SDLK_ESCAPE:
			myGame->PauseGame();
			break;
		default:
			break;
		}
	}
	nave->handleEvent(ev);	
}
void PlayState::InvincibleShip() {
	nave->Invincible();
}
bool PlayState::CheckColisions(SDL_Rect* LaserRect, bool friendly, bool reward) {	//método que comprueba la colisiones del láser		
	if (reward) {
		return nave->hit(LaserRect, friendly, reward);
	}
	else {
		auto i = scnobj.begin();
		while (i != scnobj.end() && !(*i).hit(LaserRect, friendly, false)) {
			++i;
		}
		return i != scnobj.end();
	}
	
}

void PlayState::HasDied(GameList<SceneObject>::anchor it) {
	aDestruir.push_back(it);
}

void PlayState::fireLaser(SceneObject* a) {	//Método que añade un nuevo láser al vector de láseres
	scnobj.push_back(a);
	objects.push_back(a);
}

void PlayState::EndGame(bool aux) {	//Método para acabar con el juego
	myGame->EndGame(aux);
}

void PlayState::DestroyDead() {
	for (auto i = aDestruir.begin(); i != aDestruir.end(); i++) {
		scnobj.erase(*i);
	}
	aDestruir.clear();
	for (auto i = deletions.begin(); i != deletions.end(); i++) {
		objects.erase(*i);
	}
	deletions.clear();
}

void PlayState::Save() {
	std::string guardar = "saved.txt";	
	std::ofstream a(guardar);
	myMothership->save(a);	//Se guarda la mothership, y luego se guardan, de uno en uno, todos los elementos de la lista de objetos
	for (auto i = scnobj.begin(); i != scnobj.end(); ++i) {
		a << "\n";
		(*i).save(a);
	}	
}

Texture* const PlayState::returnText(int i) {
	return myGame->devuelveText(i);
}