#ifndef PUFFERFISH_H
#define PUFFERFISH_H

#include "Obstacle.h"

class pufferfish : public Obstacle
{


private:
	float BASE_SIZE;

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

	void render(sf::RenderTarget* window);

	void update(float dt, float u);

	void update(float dt);

	const bool isCollide(const sf::FloatRect &shape);

	///////////////////////////////////////////////////
	///	
	///	\brief read the details of pufferfish from the file
	///	
	///	\param fin std::ifstream& file stream
	///	\param data Data& file stream \file Data.h
	///	\param size size_t& file no of inputs to be taken
	///	
	///	
	///////////////////////////////////////////////////
	static void read(std::ifstream &fin, Data &data, size_t &size);
};

#endif