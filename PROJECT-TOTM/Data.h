#pragma once

#include "stdafx.h"
#include "wall_gen.h"

struct Data
{

	unsigned int level_no; 
	sf::Vector2u Playerposition;
	std::vector<std::pair<sf::Vector2u, std::pair<int, int>>> wall_cordinates_sing;
	std::vector<std::vector<sf::Vector2u>> wall_cordinates_mult;

	std::vector<sf::Vector2f> marker_pos_sing;
	std::vector<std::vector<sf::Vector2f>> marker_pos_mult;


	std::vector<std::pair<sf::Vector2u, sf::Vector2u>> gun_arg; 
	std::vector<std::pair<sf::Vector2u, sf::Vector2u>> dragon_arg;
	std::vector<sf::Vector2u> Pfish_arg;
	std::vector<std::pair<sf::Vector2u, sf::Vector2u>> teleportal_arg; 
	std::vector<std::pair<sf::Vector2u, int>> spring_arg;


	///////////////////////////////////////////////////
	///	
	///	\brief read the details from the file
	///	
	///	\param data std::vector<Data>& A vector of data storing all the data
	///	
	///	
	///////////////////////////////////////////////////
	static bool read(std::vector<Data>& data); 
};
////////////////////////////////////////////////////////////
/// 
/// \struct Data
///
/// \brief information/data format used for storing level information
///		   it deals with data stored in a data.txt file 
///
///
///
////////////////////////////////////////////////////////////
