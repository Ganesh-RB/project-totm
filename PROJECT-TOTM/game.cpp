#include "game.h"

//private functions
void game::initvariables()
{
	wall_generator.add_wall(0, 20, 5, wall_generator.UP);
	wall_generator.add_wall(0, 19, 9, wall_generator.RIGHT);
	wall_generator.add_wall(8, 19, 1, wall_generator.UP);
	wall_generator.add_wall(8, 18, 2, wall_generator.RIGHT);
	wall_generator.add_wall(9, 19, 2, wall_generator.UP);
	wall_generator.add_wall(9, 17, 2, wall_generator.RIGHT);
	wall_generator.add_wall(10, 18, 10, wall_generator.UP);
	wall_generator.add_wall(9, 14, 3, wall_generator.UP);
	wall_generator.add_wall(0, 15, 3, wall_generator.RIGHT);
	wall_generator.add_wall(2, 16, 2, wall_generator.UP);
	wall_generator.add_wall(2, 14, 5, wall_generator.RIGHT);
	wall_generator.add_wall(3, 15, 3, wall_generator.UP);
	wall_generator.add_wall(4, 12, 3, wall_generator.LEFT);
	wall_generator.add_wall(0, 13, 4, wall_generator.UP);
	wall_generator.add_wall(0, 9, 3, wall_generator.RIGHT);
	wall_generator.add_wall(2, 10, 2, wall_generator.UP);
	wall_generator.add_wall(2, 8, 9, wall_generator.RIGHT);
	//FLOATERS
	wall_generator.add_wall(2, 17, 2, wall_generator.RIGHT);
	wall_generator.add_wall(5, 16, 1, wall_generator.RIGHT);
	wall_generator.add_wall(4, 11, 1, wall_generator.RIGHT);
	wall_generator.add_wall(5, 10, 1, wall_generator.RIGHT);
	wall_generator.add_wall(6, 12, 1, wall_generator.RIGHT);
	this->window = nullptr;
}


void game::initwindow()
{
	this->window =new sf::RenderWindow (sf::VideoMode(900, 600), "My first game", sf::Style::Titlebar | sf::Style::Close);
	//this->window->setFramerateLimit(60);
}
//constructors and destructors
game::game()
{
	this->initvariables();
	this->initwindow();
}

game::~game()
{
	delete this->window;
}

//accessors



const bool game::running() const
{
	return this->window->isOpen();
}

//Functions

void game::pollevents()
{
	//event checking
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			if (ev.type == sf::Event::Closed)
				this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}


void game::update(float* _dt,float* _time_mult)
{ 
	dt=*_dt;
	time_mult = *_time_mult;
	this->pollevents();
	this->player1.update(this->window,&dt,&time_mult );
	for (auto i : wall_generator.walls) {
		player1.update_collision(&i);
	}

}

void game::render()
{
	this->window->clear();
	//draw game objects
	this->player1.render(this->window);
	this->wall_generator.render(this->window);
	this->window->display();

}
