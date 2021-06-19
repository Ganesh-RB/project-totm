#pragma once
#include "player.h"

class teleporter
{
private:
	float BASE_SIZE;
	player* player_var;
	void init_variables();
	
	std::pair< sf::RectangleShape, bool > portals[2];
public:
	teleporter(sf::Vector2f portal1, sf::Vector2f portal2, player* _player_var);
	~teleporter();
	void update();
	void render(sf::RenderWindow* target);
};

