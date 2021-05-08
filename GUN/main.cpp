#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "gun.h"

using namespace sf;


int main()
{
	RenderWindow window(VideoMode(640, 400), "Gun working temporary");
	window.setFramerateLimit(60);
	
	Vector2f init_position(5.f, 100.f);
	Vector2f target(600.f, 100.f);

	gun g1(target,init_position, gunType::SpeedVariance);

	Vector2f init_position2(400.f,300.f);
	Vector2f target2(400.f, 50.f);
	gun g2(init_position2, target2, gunType::SpeedVariance);

	//RectangleShape shape(Vector2f(30.f, 30.f));
	//shape.setFillColor(Color::Magenta);
	//shape.setPosition(Vector2f(500.f, 100.f));// for sample checking

	//RectangleShape bullet(Vector2f(30.f, 30.f));
	//bullet.setPosition(init_position);
	//bullet.setFillColor(Color::Green);

	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.KeyPressed && event.key.code == Keyboard::Escape)
				window.close();

		}
			// update -> move karayacha sarv function  
			//fun_fire() flag,bullet //it will update position of bullet
			//gun::Gunfire(g1);
			g2.Gunfire();
			g1.Gunfire();

			// clear
			window.clear(Color::White);

			// draw and display
			//draw(window);
			g2.draw(window);
			g1.draw(window);

			window.display();
		
	}

	return 0;
}