#include "teleporter.h"

void teleporter::init_variables()
{
	BASE_SIZE = player_var->BASE_SIZE;
	for (auto &i : this->portals) {
		i.first.setFillColor(sf::Color::Color(255, 255,0, 255));
		i.first.setSize(sf::Vector2f(BASE_SIZE, BASE_SIZE));
		i.second = true;
	}
}

teleporter::teleporter(sf::Vector2f portal1, sf::Vector2f portal2, player* _player_var)
{
	this->player_var = _player_var;
	this->init_variables();
	portals[0].first.setPosition(portal1.x*BASE_SIZE, portal1.y*BASE_SIZE);
	portals[1].first.setPosition(portal2.x*BASE_SIZE, portal2.y*BASE_SIZE);
	
}

teleporter::~teleporter()
{
}

void teleporter::update()
{
	for (int i = 0; i < 2; i++) {
		if (!portals[i].second) {
			if (!(player_var->shape.getGlobalBounds().contains(portals[i].first.getPosition() + sf::Vector2f(BASE_SIZE / 2.f, BASE_SIZE / 2.f)))) { portals[i].second = true; }
		}
		else if ((portals[i].second) && (player_var->shape.getGlobalBounds().contains(portals[i].first.getPosition() + sf::Vector2f(BASE_SIZE / 2.f, BASE_SIZE / 2.f)))) {
			player_var->get_end_trail(player_var->movedirection, portals[i].first.getGlobalBounds());
			player_var->trails.push_back(player_var->curr_trail(&player_var->start_trail, &player_var->end_trail));
			portals[1-i].second=false;
			player_var->shape.setPosition(portals[1-i].first.getPosition());
			player_var->get_start_trail(player_var->movedirection, portals[1-i].first.getGlobalBounds());
		}
	}
}

void teleporter::render(sf::RenderWindow* target)
{
	for (const auto i : this->portals)
	{
		target->draw(i.first);
	}
}
