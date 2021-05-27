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
		dt = timer.restart().asSeconds();
		//update
		game.update(&dt, &time_mult);

		//render
		game.render();
	}
	
	return 0;
}