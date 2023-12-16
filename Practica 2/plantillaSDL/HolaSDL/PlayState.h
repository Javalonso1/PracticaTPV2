#pragma once
#include "checkML.h"
#include "GameState.h"
#include "SceneObject.h"
#include "Cannon.h"
#include "Game.h"
#include "Laser.h"
#include "Mothership.h"
#include <list>
class PlayState : public GameState
{
private:
	std::list<SceneObject*> Lista;	//Lista con todos los objetos jugables
	std::list<std::list<SceneObject*>::iterator> aDestruir;	//Lista con los objetos muertos
	Cannon* nave;			//Nave del jugador		
	Mothership* myMothership;
	bool exit;				//Booleano para terminar el juego
public:
	void LeerArchivo(std::string);	//Lee el archivo y crea el juego
	PlayState(Game*);
	~PlayState();
	void Run();			//Lanza el juego
	void Render() override;		//Renderiza
	void Update() override;		//Bucle principal
	void HandleEvents() override;	//Ejecuta eventos	
	void fireLaser(Laser*);			//Llamado cuando se dispara un láser
	bool CheckColisions(SDL_Rect*, bool);	//Comprueba las colisiones de todos los láseres		
	void EndGame();		//Cierra el juego	
	void HasDied(std::list<SceneObject*>::iterator Iterador); //Añade un objeto a la lista de muertos
	void Save(int);		//Guarda el juego
	void DestroyDead();	//Destruye a los objetos en la lista de muertos	
		
	
	
	
	
	
	
	
	
	
	
	
	
	
};

