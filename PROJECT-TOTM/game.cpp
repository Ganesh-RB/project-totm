#include "game.h"

//private functions
void game::initvariables()
{

	/* ONE BY ONE ADDING
	wall_generator.add_wall_single(2, 20, 5, wall_generator.UP);
	wall_generator.add_wall_single(2, 19, 9, wall_generator.RIGHT);
	wall_generator.add_wall_single(10, 19, 1, wall_generator.UP);
	wall_generator.add_wall_single(10, 18, 2, wall_generator.RIGHT);
	wall_generator.add_wall_single(11, 19, 2, wall_generator.UP);
	wall_generator.add_wall_single(11, 17, 2, wall_generator.RIGHT);
	wall_generator.add_wall_single(12, 18, 10, wall_generator.UP);
	wall_generator.add_wall_single(2, 15, 3, wall_generator.RIGHT);
	wall_generator.add_wall_single(4, 16, 2, wall_generator.UP);
	wall_generator.add_wall_single(4, 14, 5, wall_generator.RIGHT);
	wall_generator.add_wall_single(5, 15, 3, wall_generator.UP);
	wall_generator.add_wall_single(6, 12, 3, wall_generator.LEFT);
	wall_generator.add_wall_single(2, 13, 4, wall_generator.UP);
	wall_generator.add_wall_single(2, 9, 3, wall_generator.RIGHT);
	wall_generator.add_wall_single(4, 10, 2, wall_generator.UP);
	wall_generator.add_wall_single(4, 8, 9, wall_generator.RIGHT);*/

	//CHAIN METHOD
	wall_maker.add_wall_chain(sf::Vector2u(2U, 19U), sf::Vector2u(10U, 19U), sf::Vector2u(10U, 18U), sf::Vector2u(11U, 18U), sf::Vector2u(11U, 17U), sf::Vector2u(12U, 17U), sf::Vector2u(12U, 8U),
		sf::Vector2u(4U, 8U), sf::Vector2u(4U, 9U), sf::Vector2u(2U, 9U), sf::Vector2u(2U, 12U), sf::Vector2u(5U, 12U), sf::Vector2u(5U, 14U), sf::Vector2u(4U, 14U), sf::Vector2u(4U, 15U), sf::Vector2u(2U, 15U),
		sf::Vector2u(2U, 19U));
	//FLOATERS/SINGLE WALLS
	wall_generator.add_wall_single(11, 14, 3, wall_generator.UP);
	wall_generator.add_wall_single(4, 17, 2, wall_generator.RIGHT);
	wall_generator.add_wall_single(7, 16, 1, wall_generator.RIGHT);
	wall_generator.add_wall_single(6, 11, 1, wall_generator.RIGHT);
	wall_generator.add_wall_single(7, 10, 1, wall_generator.RIGHT);
	wall_generator.add_wall_single(8, 12, 1, wall_generator.RIGHT);
	wall_generator.add_wall_single(6, 14, 3, wall_generator.RIGHT);
	player1.add_marker_chain(sf::Vector2f(3.5f, 18.5f), sf::Vector2f(9.5f, 18.5f), sf::Vector2f(9.5f, 17.5f), sf::Vector2f(10.5f, 17.5f), sf::Vector2f(10.5f, 16.5f),
		sf::Vector2f(11.5f, 16.5f), sf::Vector2f(11.5f, 14.5f), sf::Vector2f(10.5f, 14.5f), sf::Vector2f(10.5f, 15.5f), sf::Vector2f(9.5f, 15.5f),
		sf::Vector2f(9.5f, 16.5f), sf::Vector2f(8.5f, 16.5f), sf::Vector2f(8.5f, 17.5f), sf::Vector2f(6.5f, 17.5f), sf::Vector2f(6.5f, 16.5f));
	player1.add_marker_chain(sf::Vector2f(3.5f, 18.5f), sf::Vector2f(3.5f, 16.5f), sf::Vector2f(5.5f, 16.5f), sf::Vector2f(5.5f, 15.5f), sf::Vector2f(9.5f, 15.5f),
		sf::Vector2f(9.5f, 9.5f), sf::Vector2f(11.5f, 9.5f), sf::Vector2f(11.5f, 10.5f), sf::Vector2f(10.5f, 10.5f), sf::Vector2f(10.5f, 13.5f));
	player1.add_marker_chain(sf::Vector2f(8.5f, 13.5f), sf::Vector2f(6.5f, 13.5f), sf::Vector2f(6.5, 12.5f), sf::Vector2f(7.5f, 12.5f), sf::Vector2f(7.5f, 11.5f),
		sf::Vector2f(8.5f, 11.5f), sf::Vector2f(8.5f, 9.5f), sf::Vector2f(5.5f, 9.5f), sf::Vector2f(5.5f, 11.5f), sf::Vector2f(3.5f, 11.5f), sf::Vector2f(3.5f, 10.5f),
		sf::Vector2f(6.5f, 10.5f));

	this->window = nullptr;
	this->pause = false;
	this->alive = true;
	this->is_running = true;
	this->restart_status = false;
	this->victory = false;
}


void game::initwindow()
{
	this->window = nullptr;
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
	this->GUItext.setFont(this->font1);
	this->GUItext.setCharacterSize(24);
	this->GUItext.setFillColor(sf::Color::White);
	this->GUItext.setString("NONE");
	this->deathscreen.setFont(this->font1);
	this->deathscreen.setCharacterSize(60);
	this->deathscreen.setOutlineColor(sf::Color::Red);
	this->deathscreen.setFillColor(sf::Color::Color(255, 255, 0, 255));
	this->deathscreen.setOutlineThickness(5.f);
	this->deathscreen.setString("YOU ARE DEAD !");
	this->deathscreen.setPosition(sf::Vector2f(60.f, 100.f));
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
}

//accessors



const bool game::running() const
{
	return (this->is_running && this->window->isOpen());
}

const bool game::restart() const
{
	return restart_status;
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
			if (ev.type == sf::Event::Closed) {
				this->is_running = false;
				this->window->close();
			}
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->is_running = false;
				this->window->close();
			}
			if (this->ev.key.code == sf::Keyboard::P && pause_timer.restart().asSeconds() > 0.1f)
				this->pause = (pause == true) ? false : true;
			if (this->ev.key.code == sf::Keyboard::R && (!alive || victory))
			{
				restart_status = true;
				is_running = false;
				printf("RESTARTED\n");
			}
			break;
		}
	}
}


void game::update(float* _dt, float* _time_mult)
{
	dt = *_dt;
	time_mult = *_time_mult;
	this->pollevents();

	if (((!pause) && alive) && (!player1.no_markers_remain())) {
		this->player1.update(this->window, &dt, &time_mult);
		for (auto i : wall_generator.walls) {
			player1.update_collision(&i);
		}
		for (auto i : wall_maker.walls) {
			player1.update_collision(&i);
		}
		Gun1.gunfire(this->dt);

		if (Gun1.isCollide(player1.shape.getGlobalBounds())) {
			//printf("DEAD\n");
			alive = false;
		}
		victory = player1.no_markers_remain();
	}
}

void game::render()
{
	this->window->clear();
	//draw game objects
	this->player1.render(this->window);
	this->wall_generator.render(this->window);
	this->wall_maker.render(this->window);
	this->Gun1.Render_gun(window);
	if (pause && alive) {
		GUItext.setString("PAUSED : Press P to unpause");
		this->window->draw(this->GUItext);
	}
	if (!alive) {
		this->window->draw(this->deathscreen);
		GUItext.setString("Press R to Retry Level");
		this->window->draw(this->GUItext);
	}
	if (player1.no_markers_remain()) {
		GUItext.setString("Level Complete!! Press R to play again");
		this->window->draw(this->GUItext);
	}


	this->window->display();

}
