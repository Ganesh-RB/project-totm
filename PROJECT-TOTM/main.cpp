#include <iostream>
#include "game.h"

int main()
{   
	game game;
	sf::Clock timer;
	float dt;
	float time_mult = 60.f;

	//game loop
	while(game.running())
	{  
		//update
		game.update(&dt, &time_mult);

		//render
		game.render();
		dt=timer.restart().asSeconds();
	}
	
	return 0;
}