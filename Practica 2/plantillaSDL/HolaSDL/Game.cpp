#include "checkML.h"
#include "Game.h"
#include "SDL_image.h"
#include <vector>
#include "Alien.h"
#include "Laser.h"
#include "Bunker.h"
#include "Cannon.h"
#include "texture.h"
#include <random>
#include <iostream>
#include <fstream>

const int NumDedAliens = 7;	//Constante que indica la cantidad de aliens que tienen que morir para que aumenten su velocidad de movimiento
constexpr int winWidth = 800;
constexpr int winHeight = 600;

void Game::LeerArchivo(std::string e) {		//M�todo para leer archivos y transformarlos en mapas
	std::ifstream lector(e);
	int minAlt;
	if (lector.peek() == EOF) throw "Error";	//Si no hay archivo nada m�s empezar, eso es que el nombre de mapa es incorrecto, por lo que se lanza un error
	while (lector.peek() != EOF) {			//Mientras no se haya le�do hasta el final del archivo...
		int input1;
		int input2;
		lector >> input1;		//se lee el tipo de archivo a crear
		if (input1 == 0) {		//si es 0, eso es que es una nave
			lector >> input1;	//Pilla la posici�n
			lector >> minAlt;	
			Point2D<int> ab(input1, minAlt); //Crea un Point2D que darle a la nave
			nave = new Cannon(&ab, texturas[0], this, 13);	//Crea una nave nueva
		}
		else if (input1 == 1) {	//Si es 1, es un alien
			lector >> input1;	//Pilla la posici�n
			lector >> input2;	
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al Alien
			lector >> input2;
			Alien aux(xd, *texturas[2], input2, this, minAlt - texturas[0]->getFrameHeight()); //Crea un alien
			aliens.push_back(aux);	//le a�ade al vector de aliens
		}
		else if (input1 == 2) {	//Si es un 2, es un bunker
			lector >> input1;
			lector >> input2;	//Pilla la posici�n
			Point2D<int> xd(input1, input2);	//Crea un Point2D que darle al bunker
			Bunker aux(xd, *texturas[1]);	//Crea un bunker
			bunkers.push_back(aux);	//Lo a�ade al vector de bunkers
		}		
	}
}
Game::Game() : direction(),WinHeight(), WinLong(), renderer(), window(), aliens(), lasers(), bunkers(), nave(), exit(), texturas(), dedAliens(0), mapa(){}
Game::Game(std::string e) : direction(true), WinHeight(), WinLong(), renderer(),
			window(), aliens(), lasers(), bunkers(), nave(), exit(true), texturas(), Change(false), dedAliens(0), mapa(e) {
	
}
Game::~Game() {	//Destructor del Game
	delete(nave);	//Se borra la nave
	for (int i = 0; i < NUM_TEXTURES; i++) {	//Se borran todas las texturas
		delete(texturas[i]);
	}
	SDL_DestroyRenderer(renderer);	//Se destruye el renderer
	SDL_DestroyWindow(window);	//Se destruye la ventana
	SDL_Quit();	//Se sale de SDL	
}


void Game::loadTextures() {
	texturas[0] = new Texture(renderer, "spaceship.png", 1, 1);	//Inicializa las texturas
	texturas[2] = new Texture(renderer, "aliens.png", 3, 2);
	texturas[1] = new Texture(renderer, "bunker.png", 1, 4);
	texturas[3] = new Texture(renderer, "stars.png", 1, 1);
	texturas[4] = new Texture(renderer, "laser.png", 1, 1);
}

void Game::Run() {	//M�todo al que se llama para ejecutar un tick en el juego
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw std::string("Error cargando SDL");
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
		catch (...) {	//Si salta error es	que no existe un mapa con ese nombre
			throw std::string("No existe mapa con ese nombre");
		}

		while (exit) {								//Bucle principal del juego. Mientras el m�todo "getExit" del game de true, el juego no habr� acabado								
			if (Change) {	//Si la variable Change es true, eso es que los aliens han llegado a una pared
				direction = !direction;	//Se cambia la direcci�n de movimiento
				Change = false;	//Se desactiva change
				for (int i = 0; i < aliens.size(); i++) {	//Se mueve a los aliens hacia abajo
					aliens[i].VerticalMove(veticalDown);
				}
			}
			Render();
			Update();					//Ejecuta todos los eventos del main (Render, Update...)
			SDL_Delay(50);				//Peque�o delay
			HandleEvents();
		}
	}
}

void Game::Render() {//M�todo que renderiza el juego
	SDL_Rect rect;	
	rect.h = 600;
	rect.w = 800;
	rect.x = 0;
	rect.y = 0;
	texturas[3]->renderFrame(rect, 0, 0);//Se crea el fondo lo primero de todo
	for (int i = 0; i < aliens.size(); i++) {	//Se renderizan todos los aliens
		aliens[i].Render();
	}
	for (int i = 0; i < lasers.size(); i++) {	//Se renderizan todos los lasers
		lasers[i].Render(renderer);
	}
	for (int i = 0; i < bunkers.size(); i++) {	//Se renderizan todos los bunkers
		bunkers[i].Render();		
	}
	(*nave).Render();	//Se renderiza la nave
	SDL_RenderPresent(renderer);
}



void Game::Update() {	//M�todo que llama a todos los updates del juego
	

	for (int i = 0; i < aliens.size(); i++) {
		if(aliens[i].Update()){}	//llama al update de los aliens
		else {			//si da false
			dedAliens++;	//Se suma 1 a los aliens muertos (para ver si aumentan la velocidad y eso)
			aliens.erase(aliens.begin() + i);	//Se borra el alien del vector
			i--;
		}
	}
	if (aliens.size() == 0) EndGame();	//Si no hay aliens, eso es que la partida ha acabado
	for (int i = 0; i < bunkers.size(); i++) {	
		if(bunkers[i].Update()){}	//llama al update de los bunkers
		else
		{			
			bunkers.erase(bunkers.begin() + i);	//Si da false, se elimina el bunker
			i--;
		}
	}
	if((*nave).Update()){}	//Se llama al update de la nave
	else
	{
		EndGame();	//Si da false, ha perdido todas las vidas, y la partida acaba
	}
	for (int i = 0; i < lasers.size(); i++) {
		if (lasers[i].Update()) {	//Se llama al Update de cada laser
			CheckColisions(&lasers[i]);		//Se comprueban las colisiones de ese l�ser
		}
		else {			
			lasers.erase(lasers.begin() + i);	//Se borra el l�ser si ha chocado
		}
	}
	if (dedAliens > NumDedAliens) {	//Si muere cierta cantidad de aliens, aumenta la velocidad a la que se mueven estos
		dedAliens = 0;
		for (int i = 0; i < aliens.size(); i++) aliens[i].AumentVel();	//Se le dice a todos los aliens que aumenten la velocidad
	}
}
void Game::HandleEvents() {	//M�todo que pilla un input del jugador y se lo pasa a la nave
	SDL_Event ev;
	int move = 0;
	bool shoot = false;
	while (SDL_PollEvent(&ev) != 0) {			//Lector de eventos de teclado. Lee los inputs del jugador y los pasa a variables
		switch (ev.type) {
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) {
			case SDLK_LEFT:
				move = -1;
				break;
			case SDLK_RIGHT:
				move = 1;
				break;
			case SDLK_SPACE:
				shoot = true;
				break;
			default:
				break;
			}
		}
	}	
	nave->handleEvent(move, shoot);
}
int Game::GetDirection() {	//M�todo que los aliens usan para ver si se mueven a la izquierda o derecha
	if (direction) return 1;
	else
	{
		return -1;
	}	
}
bool Game::cannotMove() {	//M�todo al que llaman los aliens de chocar con una pared
	Change = true;
	return true;
}
void Game::fireLaser(Laser* a) {	//M�todo que a�ade un nuevo l�ser al vector de l�seres
	lasers.push_back(*a);
}
void Game::CheckColisions(Laser* a) {	//m�todo que comprueba la colisiones del l�ser
	bool chocado = false;
	int i = 0;
	if (a->Friendly()) {		//Si es un l�ser de la nave
		while( i < aliens.size() && !chocado) {	//Comprueba si ha chocado con cualquiera de los aliens
			if (SDL_HasIntersection(&(a->getRect()), &(aliens[i].getRect()))) {
				aliens[i].Hit();				//De ser el caso env�a al alien y a s� mismo Hit()
				a->Hit();
				chocado = true;
			}
			i++;
		}
	}
	else{	//Si es un l�ser de la nave, checkea si choca con la nave
		if (SDL_HasIntersection(&(a->getRect()), &(nave->getRect()))) {
			a->Hit();	//De ser el caso env�a a ambos el m�todo hit
			nave->Hit();
			chocado = true;
		}
	}
	if (!chocado) {//Si no ha chocado ya
		i = 0;
		while(i<bunkers.size() && !chocado){	//Comprueba si ha chocado con cualquiera de los bunkers
			if (SDL_HasIntersection(&(a->getRect()), &(bunkers[i].getRect()))) {
				bunkers[i].Hit();	//De ser este el caso, env�a Hit a ambos
				a->Hit();
				chocado = true;
			}
			i++;
		}
	}	
}
int Game::getRandomRange(int min, int max) {	//M�todo que pilla un n�mero random
	return std::uniform_int_distribution<int>(min, max)(rnd);
}
void Game::EndGame() {	//M�todo para acabar con el juego
	exit = false;
}
bool Game::getExit() {	//M�todo que comprueba si ha acabado el juego
	return exit;
}