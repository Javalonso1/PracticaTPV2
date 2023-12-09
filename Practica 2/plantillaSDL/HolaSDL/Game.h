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
#include "GameStateMachine.h"
#include "Mothership.h"
#include "ShooterAlien.h"
#include "UFO.h"
#include <random>
#include <iostream>
#include <list>
const int NUM_TEXTURES = 6;
const int veticalDown = 13;
class Game
{
private:
	SDL_Renderer* renderer;	//Renderizador
	SDL_Window* window;		//Ventana donde se renderiza el juego
	Texture* texturas[NUM_TEXTURES];	//Array con las texturas
	GameStateMachine* myGameStateMachine;


	bool direction;			//Dirección a la que se mueven los aliens
	int WinHeight;			//Alto de pantalla
	int WinLong;			//Ancho de pantalla
	Mothership* myMothership;		//Referencia a la mothership

	std::list<SceneObject*> Lista;	//Lista con todos los objetos jugables
	std::list<std::list<SceneObject*>::iterator> aDestruir;	//Lista con los objetos muertos
	Cannon* nave;			//Nave del jugador	

	bool exit;				//Booleano para terminar el juego
	std::mt19937_64 rnd;	//Número random
	int dedAliens;			//Contador de aliens muertos
	std::string mapa;		//Nombre del mapa	
	
public:	
	Game();				//Constructor vacío
	Game(std::string);	//Constructor
	~Game();			//Destructor
	void loadTextures();			//Carga las texturas
	void Run();			//Lanza el juego
	void Render();		//Renderiza
	void Update();		//Bucle principal			

	int getRandomRange(int min, int max);	//Devuelve un númerp random
	bool getExit();		//Devuelve exit
	void EndGame();		//Cierra el juego
	SDL_Renderer* getRenderer();		
	Texture* returnTexture(int);
	
};

