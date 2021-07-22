#include "..\stdafx.h"
#include "teleporter.h"

void teleporter::init_variables()
{
	timer = 0.f;
	BASE_SIZE = player_var.BASE_SIZE;
	currentframe = sf::IntRect(0, 0, 30, 30);
	for (auto &i : this->portals) {
		i.first.setTexture(m_assets.get_texture(asset_holder::group_member_name::OJJAS,asset_holder::ojjas_textures::TELEPORTER));
		i.first.setTextureRect(currentframe);
		i.first.setScale(BASE_SIZE /i.first.getLocalBounds().width, BASE_SIZE / i.first.getLocalBounds().height);
		i.second = true;
	}
}

void teleporter::anim(float _dt)
{
		timer += 60 *_dt;
		if (timer > 20.f) {
			currentframe.left += 30;
			if (currentframe.left >= 90) { currentframe.left = 0; }
			portals[0].first.setTextureRect(currentframe);
			portals[1].first.setTextureRect(currentframe);
			timer = 0.f;
		}
		
}

teleporter::teleporter(sf::Vector2u portal1, sf::Vector2u portal2, player& _player_var, asset_holder* _assets): player_var(_player_var),m_assets(*_assets)
{
	this->Type = Obstacle::obstacle_type::Teleporter;
	this->init_variables();
	portals[0].first.setPosition(portal1.x*BASE_SIZE, portal1.y*BASE_SIZE);
	triggerpoints[0] = sf::Vector2f((portal1.x +0.5f)*BASE_SIZE, (portal1.y+0.5f)*BASE_SIZE);
	portals[1].first.setPosition(portal2.x*BASE_SIZE, portal2.y*BASE_SIZE);
	triggerpoints[1] = sf::Vector2f((portal2.x + 0.5f)*BASE_SIZE, (portal2.y + 0.5f)*BASE_SIZE);
	
}

teleporter::~teleporter()
{
}

void teleporter::update(float _dt)
{
	anim(_dt);
	for (int i = 0; i < 2; i++) {
		if (!portals[i].second) {
			if (!(player_var.shape.getGlobalBounds().contains(triggerpoints[i]))) { portals[i].second = true; }
		}
		else if ((portals[i].second) && (player_var.shape.getGlobalBounds().contains(triggerpoints[i]))) {
			player_var.get_end_trail(player_var.movedirection, portals[i].first.getGlobalBounds());
			player_var.trails.push_back(player_var.curr_trail(&player_var.start_trail, &player_var.end_trail));
			portals[1-i].second=false;
			player_var.shape.setPosition(portals[1-i].first.getPosition());
			player_var.updatemarkers();
			player_var.get_start_trail(player_var.movedirection, portals[1-i].first.getGlobalBounds());
			player_var.get_end_trail(player_var.movedirection, portals[1 - i].first.getGlobalBounds());
			m_assets.play_sound(asset_holder::group_member_name::OJJAS,asset_holder::TELEPORT);
		}
	}
}

void teleporter::render(sf::RenderTarget* target)
{
	for (const auto i : this->portals)
	{
		target->draw(i.first);
	}
}


const bool teleporter::isCollide(const sf::FloatRect& shape)
{
	return false;
}

void teleporter::read(std::ifstream & fin, Data &data, size_t & size)
{
	unsigned temp_var1, temp_var2, temp_var3, temp_var4;

	for (size_t i = 0; i < size; i++)
	{
		fin >> temp_var1 >> temp_var2;
		fin >> temp_var3 >> temp_var4;

		data.teleportal_arg.push_back(std::pair< sf::Vector2u, sf::Vector2u >(sf::Vector2u(temp_var1, temp_var2), sf::Vector2u(temp_var3, temp_var4)));
	}

}