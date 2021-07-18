#pragma once

#include "stdafx.h"
#include "wall_gen.h"

struct Data
{

	unsigned int level_no; // 1
	sf::Vector2u Playerposition;// like 1 2
	std::vector<std::pair<sf::Vector2u, std::pair<int, int>>> wall_cordinates_sing; //like 1 2,3 2,3 4,4 3,2 3,1 2,8 7
	std::vector<std::vector<sf::Vector2u>> wall_cordinates_mult;

	std::vector<sf::Vector2u> marker_pos_sing;
	std::vector<std::vector<sf::Vector2f>> marker_pos_mult;


	std::vector<std::pair<sf::Vector2u, sf::Vector2u>> gun_arg; //like 1 2,3 4:1 2,3 4
	std::vector<std::pair<sf::Vector2u, sf::Vector2u>> dragon_arg; //like 1 2,3 4:1 2,3 4
	std::vector<sf::Vector2u> Pfish_arg; //like 1 2,3 4,2 3
	std::vector<std::pair<sf::Vector2u, sf::Vector2u>> teleportal_arg; //like 1 2,3 4:1 2,3 4
	std::vector<std::pair<sf::Vector2u, int>> spring_arg; //like 1 2,3 4,2 3

	static bool read(std::vector<Data>&); //it will read all object once 
};

