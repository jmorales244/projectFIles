#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());

auto& TIEFighter(manager.addEntity());

auto& asteroid(manager.addEntity());


enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupEnviromentals
};


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}

		isRunning = true;
	}
	map = new Map();

	//ecs implementation of objects/players
	//Map::LoadMap("fileName", width, height) - Uploads drawing in window based on tile composition 
	Map::LoadMap("p32x32.map", 32, 32);
	//object.addComponent<TransformComponent>(xLoc, yLoc, height, width, scale);
	
	player.addComponent<TransformComponent>(196.0f, 750.0f, 128, 128, 1); //set position lower area, middle of window 
	player.addComponent<SpriteComponent>("player_frames.png", true);

	//Gives controll to the player for the x-wing 
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	//Enemies Spawn
	TIEFighter.addComponent<TransformComponent>(0.0f, 300.0f, 128, 128, 1);
	TIEFighter.addComponent<SpriteComponent>("TIE_Fighter.png");
	TIEFighter.addGroup(groupEnemies);

	TIEFighter.addComponent<TransformComponent>(128.0f, 300.0f, 128, 128, 1);
	TIEFighter.addComponent<SpriteComponent>("TIE_Fighter.png");
	TIEFighter.addGroup(groupEnemies);
	
	TIEFighter.addComponent<TransformComponent>(256.0f, 300.0f, 128, 128, 1);
	TIEFighter.addComponent<SpriteComponent>("TIE_Fighter.png");
	TIEFighter.addGroup(groupEnemies);
	
	TIEFighter.addComponent<TransformComponent>(384.0f, 300.0f, 128, 128, 1);
	TIEFighter.addComponent<SpriteComponent>("TIE_Fighter.png");
	TIEFighter.addGroup(groupEnemies);
	
	TIEFighter.addComponent<TransformComponent>(128.0f, 100.0f, 128, 128, 1);
	TIEFighter.addComponent<SpriteComponent>("TIE_Fighter.png");
	TIEFighter.addGroup(groupEnemies);
	
	TIEFighter.addComponent<TransformComponent>(256.0f, 200.0f, 128, 128, 1);
	TIEFighter.addComponent<SpriteComponent>("TIE_Fighter.png");
	TIEFighter.addGroup(groupEnemies);
	
	TIEFighter.addComponent<TransformComponent>(384.0f, 100.0f, 128, 128, 1);
	TIEFighter.addComponent<SpriteComponent>("TIE_Fighter.png");
	TIEFighter.addGroup(groupEnemies);

	//TransformComponent(float xloc, float yloc, int height, int width, int scale)
	asteroid.addComponent<TransformComponent>(0.0f,150.0f,128,128,1);
	asteroid.addComponent<SpriteComponent>("asteroid.png");
	asteroid.addComponent<ColliderComponent>("asteroid");
	asteroid.addGroup(groupMap);

	asteroid.addComponent<TransformComponent>(100.0f, 500.0f, 128, 128, 1);
	asteroid.addComponent<SpriteComponent>("asteroid.png");
	asteroid.addComponent<ColliderComponent>("asteroid");
	asteroid.addGroup(groupMap);
	



}

void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}


void Game::update()
{
	manager.refresh();
	manager.update();
	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
	

}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& worldEnviromentals(manager.getGroup(groupEnviromentals));

void Game::render()
{
	SDL_RenderClear(renderer);
	//Creates background
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	for (auto& w : worldEnviromentals)
	{
		w->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTitle(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 64, 64, id);
	tile.addGroup(groupMap);
}
