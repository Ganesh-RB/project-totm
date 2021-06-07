#pragma once
#include "player.h"
#include "wall_gen.h"
#include "gun.h"
class game
{
private:
	//window

	sf::Event ev;
	//private functions
	float dt;
	float time_mult;
	bool pause;
	bool alive;
	bool is_running;
	bool restart_status;
	bool victory;
	sf::Clock pause_timer;
	player player1{ 3.f,18.f };
	gun Gun1{ sf::Vector2u(11U,12U),sf::Vector2u(9U,12U),gunType::Simple };

	// initializers
	void initvariables();
	void initwindow();
	void initfonts();
	void inittext();
	//fonts
	sf::Font font1;
	//text
	sf::Text GUItext;
	sf::Text deathscreen;
public:
	sf::RenderWindow* window;
	//constructor and destructor
	game();
	virtual ~game();
	//sf::Sprite sprite1;
	//sf::Texture texture;
	const bool running() const;
	const bool restart() const;
	wall_gen wall_generator{ sf::Color::Color(0,0,255,120),30.f };
	wall_gen wall_maker{ sf::Color::Color(255,255,255,120),30.f };
	//functions
	void pollevents();
	void update(float* _dt, float* _time_mult);
	void render();
};

