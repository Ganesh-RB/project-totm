#include "wall_gen.h"
wall_gen::wall_gen(sf::Color _color, float _base_size)
{
	wall_colour = _color;
	base_size = _base_size;
	chain_point = sf::Vector2u(0U, 0U);
	chain_start = true;
}

wall_gen::~wall_gen()
{
}

void wall_gen::add_wall_single(float x_coord, float y_coord, float len, wall_dir_no dir)
{
	sf::RectangleShape temp;
	temp.setFillColor(wall_colour);
	temp.setPosition(x_coord*base_size, y_coord*base_size);
	switch (dir)
	{
	case LEFT:
		temp.setSize(sf::Vector2f(-len * base_size, base_size));
		break;
	case RIGHT:
		temp.setSize(sf::Vector2f(len * base_size, base_size));
		break;
	case UP:
		temp.setSize(sf::Vector2f(base_size, -len * base_size));
		break;
	case DOWN:
		temp.setSize(sf::Vector2f(base_size, len*base_size));
		break;
	}
	walls.push_back(temp);
}

void wall_gen::add_wall_chain()
{
	chain_start = true;
}



void wall_gen::render(sf::RenderTarget * target)
{
	for (auto i : this->walls)
	{
		target->draw(i);
	}
}

