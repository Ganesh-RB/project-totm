#include "game.h"

//private functions
void game::initvariables()
{
	wall_generator.add_wall(2, 20, 5, wall_generator.UP);
	wall_generator.add_wall(2, 19, 9, wall_generator.RIGHT);
	wall_generator.add_wall(10, 19, 1, wall_generator.UP);
	wall_generator.add_wall(10, 18, 2, wall_generator.RIGHT);
	wall_generator.add_wall(11, 19, 2, wall_generator.UP);
	wall_generator.add_wall(11, 17, 2, wall_generator.RIGHT);
	wall_generator.add_wall(12, 18, 10, wall_generator.UP);
	wall_generator.add_wall(11, 14, 3, wall_generator.UP);
	wall_generator.add_wall(2, 15, 3, wall_generator.RIGHT);
	wall_generator.add_wall(4, 16, 2, wall_generator.UP);
	wall_generator.add_wall(4, 14, 5, wall_generator.RIGHT);
	wall_generator.add_wall(5, 15, 3, wall_generator.UP);
	wall_generator.add_wall(6, 12, 3, wall_generator.LEFT);
	wall_generator.add_wall(2, 13, 4, wall_generator.UP);
	wall_generator.add_wall(2, 9, 3, wall_generator.RIGHT);
	wall_generator.add_wall(4, 10, 2, wall_generator.UP);
	wall_generator.add_wall(4, 8, 9, wall_generator.RIGHT);
	//FLOATERS
	wall_generator.add_wall(4, 17, 2, wall_generator.RIGHT);
	wall_generator.add_wall(7, 16, 1, wall_generator.RIGHT);
	wall_generator.add_wall(6, 11, 1, wall_generator.RIGHT);
	wall_generator.add_wall(7, 10, 1, wall_generator.RIGHT);
	wall_generator.add_wall(8, 12, 1, wall_generator.RIGHT);
	this->window = nullptr;
	this->pause = false;
}


void game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(900, 600), "My first game", sf::Style::Titlebar | sf::Style::Close);
	//this->window->setFramerateLimit(60);
}
void game::initfonts()
{
	if (!font1.loadFromFile("Fonts/Dosis-Light.ttf")) {
		printf("Error::Game::initfonts failed to load font1 \n");
	}
}
void game::inittext()
{
	this->pausetext.setFont(this->font1);
	this->pausetext.setCharacterSize(24);
	this->pausetext.setFillColor(sf::Color::White);
	this->pausetext.setString("PAUSE");
}
//constructors and destructors
game::game()
{
	this->initvariables();
	this->initwindow();
	this->initfonts();
	this->inittext();
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
			if (this->ev.key.code == sf::Keyboard::P && pause_timer.restart().asSeconds() > 0.1f)

				this->pause = (pause == true) ? false : true;
			break;
		}
	}
}


void game::update(float* _dt, float* _time_mult)
{
	dt = *_dt;
	time_mult = *_time_mult;
	this->pollevents();
	if (pause == false) {
		this->player1.update(this->window, &dt, &time_mult);
		for (auto i : wall_generator.walls) {
			player1.update_collision(&i);
		}
	}
}

void game::render()
{
	this->window->clear();
	//draw game objects
	this->player1.render(this->window);
	this->wall_generator.render(this->window);
	if (pause == true) {
		this->window->draw(this->pausetext);
	}
	this->window->display();

}
