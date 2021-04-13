#include "game.h"

//private functions
void game::initvariables()
{
	/*These lines are only to intialize some walls to test player movement,
	will be removed later on*/
	for (int i = 0; i < 7; i++) {
		test[i].setFillColor(sf::Color::Blue);
	}
	test[0].setSize(sf::Vector2f(150.f, 30.f));
	test[0].setPosition(0.f, 0.f);
	test[1].setSize(sf::Vector2f(30.f, 150.f));
	test[1].setPosition(0.f, 0.f);
	test[2].setSize(sf::Vector2f(90.f, 30.f));
	test[2].setPosition(0.f, 120.f);
	test[3].setSize(sf::Vector2f(30.f, 180.f));
	test[3].setPosition(120.f, 30.f);
	test[4].setSize(sf::Vector2f(30.f, 30.f));
	test[4].setPosition(60.f, 60.f);
	test[5].setSize(sf::Vector2f(30.f, 90.f));
	test[5].setPosition(60.f, 150.f);
	test[6].setSize(sf::Vector2f(60.f, 30.f));
	test[6].setPosition(90.f, 210.f);


	
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
	for (int i = 0; i < 7; i++) {
		player1.update_collision(&test[i]);
	}

}

void game::render()
{
	this->window->clear();
	//draw game objects
	this->player1.render(this->window);
	for (int i = 0; i < 7; i++) {
		window->draw(test[i]);
	}
	this->window->display();

}
