#pragma once
#include "player.h"

class game
{
private:
	//variables
	
	//window
	sf::RenderWindow* window;
	sf::Event ev;
	//private functions
	float dt;
	float time_mult;
	player player1{30.f,60.f};
	void initvariables();
	void initwindow();
public:
	//constructor and destructor
	game();
	virtual ~game();
	sf::Sprite sprite1;
	sf::Texture texture;
	const bool running() const;
	sf::RectangleShape test[8];
	//functions
	void pollevents();
	void update(float* _dt,float* _time_mult);
	void render();
};

