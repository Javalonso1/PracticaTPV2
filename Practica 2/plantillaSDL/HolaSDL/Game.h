#pragma once
#include "checkML.h"
#include "SDL_image.h"
#include <vector>
#include "Alien.h"
#include "Laser.h"
#include "Bunker.h"
#include "Cannon.h"
#include "texture.h"
#include "SceneObject.h"
#include "Mothership.h"
#include "ShooterAlien.h"
#include "UFO.h"
#include <random>
#include <iostream>
#include <list>
const int NUM_TEXTURES = 5;
const int veticalDown = 13;
class Game
{
private:
	bool direction;			//Direcci�n a la que se mueven los aliens
	bool Change;			//Indica que se produce un cambio de direcci�n
	int WinHeight;			//Alto de pantalla
	int WinLong;			//Ancho de pantalla
	SDL_Renderer* renderer;	//Renderizador
	SDL_Window* window;		//Ventana donde se renderiza el juego
	Mothership* myMothership;

	std::list<SceneObject*> Lista;
	Cannon* nave;			//Nave del jugador	

	/*std::vector<Alien> aliens;		//Array de aliens
	std::vector<Laser> lasers;		//Array de l�seres
	std::vector<Bunker> bunkers;	//Array de b�nkeres	
	UFO* ufo;*/

	bool exit;				//Booleano para terminar el juego
	Texture* texturas[NUM_TEXTURES];	//Array con las texturas
	std::mt19937_64 rnd;	//N�mero random
	int dedAliens;			//Contador de aliens muertos
	std::string mapa;		//Nombre del mapa
	std::string guardado;		//Nombre del mapa guardado

	std::list<SceneObject*> objetos;
public:
	void LeerArchivo(std::string);	//Lee el archivo y crea el juego
	Game();				//Constructor vac�o
	Game(std::string, std::string);	//Constructor
	~Game();			//Destructor
	void Run();			//Lanza el juego
	void Render();		//Renderiza
	void Update();		//Bucle principal
	void HandleEvents();	//Ejecuta eventos
	int GetDirection();	//Devuelve la direcci�n de los aliens
	bool cannotMove();	//Es llamado cuando los aliens chocan con una pared
	void fireLaser(Laser*);			//Llamado cuando se dispara un l�ser
	void CheckColisions(SDL_Rect*, bool, Laser*);	//Comprueba las colisiones de todos los l�seres
	int getRandomRange(int min, int max);	//Devuelve un n�merp random
	bool getExit();		//Devuelve exit
	void EndGame();		//Cierra el juego
	void loadTextures();			//Carga las texturas
	SDL_Renderer* getRenderer();
	void HasDied(std::list<SceneObject*>::iterator Iterador);
	void Save();
};

