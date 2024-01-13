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
#include "GameStateMachine.h"
#include "MainMenuState.h"

const int NUM_TEXTURES = 18;
const int veticalDown = 13;
class Game
{
private:
	int WinHeight;			//Alto de pantalla
	int WinLong;			//Ancho de pantalla
	SDL_Renderer* renderer;	//Renderizador
	SDL_Window* window;		//Ventana donde se renderiza el juego
	Texture* texturas[NUM_TEXTURES];	//Array con las texturas
	std::string mapa;		//Nombre del mapa	
	PlayState* myPlayState;		
	GameStateMachine* DeusEx;
	SDL_Event manolo;

	bool exit;
	bool goback = false;
	bool guardado = false;
	bool pause = false;

public:	
	Game();				//Constructor vacío
	Game(std::string);	//Constructor
	~Game();			//Destructor
	void Run();
	void loadTextures();			//Carga las texturas	
	SDL_Renderer* const getRenderer();	
	Texture* devuelveText(int) const;
	void ExitGame();
	void pushState(GameState*);
	void popState();
	void replaceState(GameState*);
	void continuar(bool);
	void PauseGame();
	void EndGame(bool);
	std::string GetMap() const;
};

