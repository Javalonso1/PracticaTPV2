//Pablo Marcos Serrano
//Javier Alonso Ruiz

#include "checkML.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"
#include "InvadersError.h"

using namespace std;

using uint = unsigned int;

void firstTest()
{	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::string Nombre1 = "trinchera.txt";
		
	
				
		try {
			Game a(Nombre1);
			a.Run(); //Contrusctor del game. Le damos el nombre del archivo del mapa			
		}
		catch (InvadersError error) {		//Detecta si hay algún error en este proceso, y lanza el error de ser el caso
			cout << error.what();
		}	
	
}

int main(int argc, char* argv[])
{
	firstTest();
	return 0;
}
