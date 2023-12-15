#pragma once
#include "checkML.h"
#include "PlayState.h"
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
const int NUM_TEXTURES = 6;
const int veticalDown = 13;
class Game
{
private:
	bool direction;			//Dirección a la que se mueven los aliens
	int WinHeight;			//Alto de pantalla
	int WinLong;			//Ancho de pantalla
	SDL_Renderer* renderer;	//Renderizador
	SDL_Window* window;		//Ventana donde se renderiza el juego
	Texture* texturas[NUM_TEXTURES];	//Array con las texturas
	std::string mapa;		//Nombre del mapa	
	PlayState* myPlayState;		
public:	
	Game();				//Constructor vacío
	Game(std::string);	//Constructor
	~Game();			//Destructor
	void loadTextures();			//Carga las texturas
	SDL_Renderer* getRenderer();	
	Texture* devuelveText(int);
};

