#include <iostream>
#include "game.h"

int main()
{

	sf::Clock timer;
	float dt;
	float time_mult = 60.f;//fps whose speed is being selected
	sf::RenderWindow display(sf::VideoMode(900, 600), "My first game", sf::Style::Titlebar | sf::Style::Close);
	bool restart1 = true;
	while (restart1) {
		game game1;
		game1.window = &display;
		//game loop
		while (game1.running())
		{
			dt = timer.restart().asSeconds();
			//update
			game1.update(&dt, &time_mult);

			//render
			game1.render();
		}
		restart1 = game1.restart();
	}
	return 0;
}