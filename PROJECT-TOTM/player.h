#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class player
{
private:
	sf::RectangleShape shape;
	void initvariables();
	const void initshape();
	float movementspeed;
	//varaiables needed for time independent implementation
	float dt;
	float time_mult;
	//needed to draw trail lines
	sf::Vector2f start_trail;
	sf::Vector2f end_trail;
public:
	//cons and decons
	player(float _x=0.f, float _y=0.f);
	virtual ~player();
	//movement variables
	bool moving;
	int movedirection;
	//returns coord of player object
	sf::Vector2f getcoord();
	//updates input and movement
	void updateinput();
	//checks for window collison
	void updatewindowcollision(sf::RenderTarget* target);
	void update_collision(sf::RectangleShape*);
	//generic update and vender
	void update(sf::RenderTarget* target,float* _dt,float* _time_mult);
	void render(sf::RenderTarget* target);
	//vector where all previously made trails are stored
	std::vector<sf::RectangleShape> trails;
	//shape which is for trail being drawn(if any)
	sf::RectangleShape curr_trail(sf::Vector2f* start,sf::Vector2f* end);
	//sets trail end depending on movemenet direction
	void getendtrail(int);
};

