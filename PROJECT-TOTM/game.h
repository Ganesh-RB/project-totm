#pragma once
#include "player.h"
#include "wall_gen.h"
class game
{
private:
	//window
	sf::RenderWindow* window;
	sf::Event ev;
	//private functions
	float dt;
	float time_mult;
	bool pause;
	sf::Clock pause_timer;
	player player1{ 90.f,540.f };
	// initializers
	void initvariables();
	void initwindow();
	void initfonts();
	void inittext();
	//fonts
	sf::Font font1;
	//text
	sf::Text pausetext;
public:
	//constructor and destructor
	game();
	virtual ~game();
	sf::Sprite sprite1;
	sf::Texture texture;
	const bool running() const;
	wall_gen wall_generator{ sf::Color::Color(0,0,255,120),30.f };
	//functions
	void pollevents();
	void update(float* _dt, float* _time_mult);
	void render();
};

