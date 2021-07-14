#include "..\stdafx.h"
#include "spring.h"

void spring::initvariables()
{
	bounce_animation = false;
	timer_bounce = 0.f;
	timer = 0.f;

	anim_flash = 1.f;
	currentframe = sf::IntRect(0, 0, 30, 30);
	spring_sprite.setTexture(m_assets.get_texture(asset_holder::group_member_name::OJJAS,asset_holder::ojjas_textures::SPRING));
	spring_sprite.setTextureRect(currentframe);
	spring_sprite.setScale(BASE_SIZE/ spring_sprite.getLocalBounds().width, BASE_SIZE / spring_sprite.getLocalBounds().height);
	is_active = true;
	spring_sprite.setOrigin(BASE_SIZE / 2.f, BASE_SIZE / 2.f);
	spring_sprite.setPosition(trigger_point);
	switch (dir) {
	case spring_dir::DOWN_RIGHT:
		directions.first[0] = player::move_dir_no::MOVE_UP;
		directions.first[1] = player::move_dir_no::MOVE_RIGHT;
		directions.second[0] = player::move_dir_no::MOVE_LEFT;
		directions.second[1] = player::move_dir_no::MOVE_DOWN;
		
		break;
	case spring_dir::DOWN_LEFT:
		directions.first[0] = player::move_dir_no::MOVE_UP;
		directions.first[1] = player::move_dir_no::MOVE_LEFT;
		directions.second[0] = player::move_dir_no::MOVE_RIGHT;
		directions.second[1] = player::move_dir_no::MOVE_DOWN;

		spring_sprite.setRotation(90.f);
		break;

	case spring_dir::UP_LEFT:
		directions.first[0] = player::move_dir_no::MOVE_DOWN;
		directions.first[1] = player::move_dir_no::MOVE_LEFT;
		directions.second[0] = player::move_dir_no::MOVE_RIGHT;
		directions.second[1] = player::move_dir_no::MOVE_UP;
		spring_sprite.setRotation(180.f);
		break;

	case spring_dir::UP_RIGHT:
		directions.first[0] = player::move_dir_no::MOVE_DOWN;
		directions.first[1] = player::move_dir_no::MOVE_RIGHT;
		directions.second[0] = player::move_dir_no::MOVE_LEFT;
		directions.second[1] = player::move_dir_no::MOVE_UP;
		spring_sprite.setRotation(-90.f);
		break;
	}
	
}

void spring::animation(float _dt)
{
    timer += 60* anim_flash* _dt;
	if (timer > 60.f) { anim_flash = -1.f; }
	if (timer < 0.f) { anim_flash = 1.f; }
	spring_sprite.setColor(sf::Color::Color(120 + (int)(timer * 2), 120 + (int)(timer * 2), 120 + (int)(timer * 2), 255));
	if (bounce_animation) {
		timer_bounce += 60 * _dt;
		if (timer_bounce > 15.f) {
			timer_bounce = 0.f;
			bounce_animation = false;
			currentframe.left = 0;
			spring_sprite.setTextureRect(currentframe);
		}
	}
}

spring::spring(sf::Vector2f _position,spring_dir _dir, player &_player_var, asset_holder* asset_source): player_var(_player_var),m_assets(*asset_source)
{
	BASE_SIZE = player_var.BASE_SIZE;
	spring_sprite.setPosition(_position*BASE_SIZE);
	trigger_point = spring_sprite.getPosition() + sf::Vector2f(BASE_SIZE / 2.f, BASE_SIZE / 2.f);
	dir = _dir;
	initvariables();
}

spring::~spring()
{
}

void spring::update(float _dt)
{
	animation(_dt);
	if (!is_active) {
		if (!player_var.shape.getGlobalBounds().contains(trigger_point)) {
			is_active = true;
			bounce_animation = true;
			currentframe.left = 30;
			spring_sprite.setTextureRect(currentframe);
			m_assets.play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BOUNCE);
		}
	}
	else if (is_active && player_var.shape.getGlobalBounds().contains(trigger_point)){
		if (player_var.movedirection == directions.first[0]) {
			player_var.get_end_trail(player_var.movedirection, spring_sprite.getGlobalBounds());
			player_var.trails.push_back(player_var.curr_trail(&player_var.start_trail, &player_var.end_trail));
			is_active= false;
			player_var.movedirection = directions.first[1];
			player_var.last_moving_direction = player_var.movedirection;
			player_var.shape.setPosition(spring_sprite.getPosition() - sf::Vector2f(BASE_SIZE / 2.f, BASE_SIZE / 2.f));
			player_var.get_start_trail(player_var.movedirection, spring_sprite.getGlobalBounds());
			player_var.previous_moving = false;
			player_var.spring_flag = true;
		}
		if (player_var.movedirection == directions.second[0]) {
			player_var.get_end_trail(player_var.movedirection, spring_sprite.getGlobalBounds());
			player_var.trails.push_back(player_var.curr_trail(&player_var.start_trail, &player_var.end_trail));
			is_active = false;
			player_var.movedirection = directions.second[1];
			player_var.last_moving_direction = player_var.movedirection;
			player_var.shape.setPosition(spring_sprite.getPosition()-sf::Vector2f(BASE_SIZE/2.f,BASE_SIZE/2.f));
			player_var.get_start_trail(player_var.movedirection, spring_sprite.getGlobalBounds());
			player_var.previous_moving = false;
			player_var.spring_flag = true;
		}
	}
}

void spring::render(sf::RenderTarget* target)
{
	target->draw(spring_sprite);
}
