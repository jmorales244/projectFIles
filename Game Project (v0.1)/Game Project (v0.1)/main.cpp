#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"

Game* game = nullptr;

using namespace std;

int main(int argc, char *argv[])
{
	//Delaying Framerate
	const int FPS = 60; 
	const int frameDelay = 300 / FPS;

	Uint32 frameStart;
	int frameTime;
	

	game = new Game();
	//Window Size
	game->init("X-Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 1000, false);
	
	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		//In order to use milliseconds for the delay to seem fast for the ship 
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}


	}

	game->clean();


	return 0;
}