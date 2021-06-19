#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>



class pufferfish
{


private:
	sf::Vector2f PlayerSize;

	sf::Vector2f FishPosition;

	sf::Vector2f FishPosition1;

	sf::Vector2f FishPosition2;

	sf::Vector2f FishSize;

	sf::RectangleShape Fish;

	void Fish1();

	float t;

public:
	pufferfish(sf::Vector2u Fishposition);

	virtual ~pufferfish();

	void Render_fish(sf::RenderWindow* window);

	void Updatefish(float dt, float u);

	const bool isCollide(const sf::FloatRect &shape);
};
