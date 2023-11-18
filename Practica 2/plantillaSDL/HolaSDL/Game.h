#pragma once
#include "checkML.h"
#include "SDL_image.h"
#include <vector>
#include "Alien.h"
#include "Laser.h"
#include "Bunker.h"
#include "Cannon.h"
#include "texture.h"
#include <random>
#include <iostream>
const int NUM_TEXTURES = 5;
const int veticalDown = 13;
class Game
{
private:
	bool direction;			//Dirección a la que se mueven los aliens
	bool Change;			//Indica que se produce un cambio de dirección
	int WinHeight;			//Alto de pantalla
	int WinLong;			//Ancho de pantalla
	SDL_Renderer* renderer;	//Renderizador
	SDL_Window* window;		//Ventana donde se renderiza el juego
	std::vector<Alien> aliens;		//Array de aliens
	std::vector<Laser> lasers;		//Array de láseres
	std::vector<Bunker> bunkers;	//Array de búnkeres
	Cannon* nave;			//Nave del jugador
	bool exit;				//Booleano para terminar el juego
	Texture* texturas[NUM_TEXTURES];	//Array con las texturas
	std::mt19937_64 rnd;	//Número random
	int dedAliens;			//Contador de aliens muertos
	std::string mapa;		//Nombre del mapa
public:
	void LeerArchivo(std::string);	//Lee el archivo y crea el juego
	Game();				//Constructor vacío
	Game(std::string);	//Constructor
	~Game();			//Destructor
	void Run();			//Lanza el juego
	void Render();		//Renderiza
	void Update();		//Bucle principal
	void HandleEvents();	//Ejecuta eventos
	int GetDirection();	//Devuelve la dirección de los aliens
	bool cannotMove();	//Es llamado cuando los aliens chocan con una pared
	void fireLaser(Laser*);			//Llamado cuando se dispara un láser
	void CheckColisions(Laser* a);	//Comprueba las colisiones de todos los láseres
	int getRandomRange(int min, int max);	//Devuelve un númerp random
	bool getExit();		//Devuelve exit
	void EndGame();		//Cierra el juego
	void loadTextures();			//Carga las texturas
};

