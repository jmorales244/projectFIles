#pragma once
#include "Game.hpp"

class Map
{
public:

	Map();
	~Map();

	void LoadMap(int arr[40][20]);
	void DrawMap();

private:

	SDL_Rect src, dest;
	SDL_Texture* space;
	//SDL_Texture* asteroid;
	//SDL_Texture* planet; Might add planet tatooine, not sure yet as top down view may look weird 
	SDL_Texture* backgroundTexture;

	int map[40][20];

};