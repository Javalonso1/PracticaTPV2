#pragma once
#include "checkML.h"
#include "GameState.h"
#include "SceneObject.h"
#include "Cannon.h"
#include "texture.h"
#include "Game.h"
#include "Laser.h"
#include "Mothership.h"
#include <list>
#include "gameList.h"

class PlayState : public GameState
{
private:
	//std::list<SceneObject*> Lista;	//Lista con todos los objetos jugables
	std::list<GameList<SceneObject>::anchor> aDestruir;	//Lista con los objetos muertos
	Cannon* nave;			//Nave del jugador		
	Mothership* myMothership;	

	GameList<SceneObject> scnobj;
public:
	void LeerArchivo(std::string);	//Lee el archivo y crea el juego
	PlayState(Game*);
	~PlayState();	
	void Render() const override;	//Renderiza
	void Update() override;			//Bucle principal
	void HandleEvents(const SDL_Event&) override;	//Ejecuta eventos	
	void fireLaser(SceneObject*);			//Llamado cuando se dispara un láser
	bool CheckColisions(SDL_Rect*, bool, bool);	//Comprueba las colisiones de todos los láseres		
	void EndGame(bool);			//Cierra el juego	
	void HasDied(GameList<SceneObject>::anchor Iterador); //Añade un objeto a la lista de muertos
	void Save() override;			//Guarda el juego
	void DestroyDead();		//Destruye a los objetos en la lista de muertos		
	Texture* const returnText(int);
};

