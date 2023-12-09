#pragma once
#include "checkML.h"
#include "GameState.h"
#include "SceneObject.h"
#include "Cannon.h"
#include "Mothership.h"
#include "Laser.h"
#include <string>
#include <list>
class PlayState : public GameState
{
private:
	Game* myGame;
	std::list<SceneObject*> Lista;	//Lista con todos los objetos jugables
	std::list<std::list<SceneObject*>::iterator> aDestruir;	//Lista con los objetos muertos
	Cannon* nave;			//Nave del jugador		
	Mothership* myMothership;		//Referencia a la mothership
public:
	void LeerArchivo(std::string);	//Lee el archivo y crea el juego
	PlayState(std::string,Game*);
	~PlayState();
	void HandleEvents();	//Ejecuta eventos
	int GetDirection();	//Devuelve la dirección de los aliens		
	void fireLaser(Laser*);			//Llamado cuando se dispara un láser
	int GetDirection();	//Devuelve la dirección de los aliens	
	bool CheckColisions(SDL_Rect*, bool);	//Comprueba las colisiones de todos los láseres
	void HasDied(std::list<SceneObject*>::iterator Iterador); //Añade un objeto a la lista de muertos
	void DestroyDead();	//Destruye a los objetos en la lista de muertos
	void Save(int);		//Guarda el juego	
};

