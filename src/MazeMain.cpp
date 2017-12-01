#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main(int argc, char *argv[]) 
{
	std::cout << "Loading Maze Game" << std::endl;
	//Set Game Variables
	sf::RenderWindow window(sf::VideoMode(800, 592), "a-Maze'n Game");
	sf::Clock gameClock;
	float gameTime = 0.0f;
	float currentTime = 0.0f;
	float delta = 1.0f / 30.0f;
	bool running = true;
	
	//Set Game Levels
	//To add more levels just add the tmx name to the array
	int level_index = 0;
	std::string levels [] = { "maze_game_level_1.tmx", "maze_game_level_2.tmx" };
	int levels_length = (sizeof(levels) / sizeof(std::string));

	std::cout << "Game Elapsed Time Before Init in milliseconds: " << gameClock.getElapsedTime().asMilliseconds() << std::endl;

	Game game;

	if (!game.Init(levels[level_index]))
	{
		std::cout << "Error Loading Game" << std::endl;
		return 0;
	}

	std::cout << "Game Elapsed Time After Init in milliseconds: " << gameClock.getElapsedTime().asMilliseconds() << std::endl;

	while (running) 
	{
		bool drawRequested = false;
		//Events
		sf::Event ev;
		while (window.pollEvent(ev)) 
		{
			if (ev.type == sf::Event::Closed) 
			{
				running = false;
			}
		}

		//Check game over
		if (game.isGameOver())
		{
			level_index = 0;
			game.Shutdown();
			game.Init(levels[level_index]);
		}

		if (game.loadNextLevel())
		{
			++level_index;

			if (level_index > levels_length - 1)
			{
				level_index = 0;
			}

			game.Reset();
			game.IncreaseDifficultyModifier();			
			std::cout << "New Level Difficulty: " << game.GetDifficultyModifier() << std::endl;
			game.Init(levels[level_index]);
		}

		//Game Update
		while ((currentTime = gameClock.getElapsedTime().asSeconds()) > gameTime) 
		{
			gameTime += delta;
			drawRequested = true;
			//Update the game.
			game.Update(delta);			
		}		

		//Draw
		if (drawRequested) 
		{
			window.clear();
			window.draw(game);			
			window.display();
		}
	}

	game.Shutdown();
	window.close();
	return 0;
}