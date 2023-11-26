//Pablo Marcos Serrano
//Javier Alonso Ruiz

#include "checkML.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"

using namespace std;

using uint = unsigned int;

void firstTest()
{	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	
	
				
		try {
			Game a("trinchera.txt", "guardar.txt");
			a.Run(); //Contrusctor del game. Le damos el nombre del archivo del mapa			
		}
		catch (string error) {		//Detecta si hay algún error en este proceso, y lanza el error de ser el caso
			cout << error;
		}	
	
}

int main(int argc, char* argv[])
{
	firstTest();
	return 0;
}
