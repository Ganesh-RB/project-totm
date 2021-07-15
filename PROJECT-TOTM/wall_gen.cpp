#include "stdafx.h"
#include "wall_gen.h"
wall_gen::wall_gen(float _base_size)
{
	base_size = _base_size;
	unsigned base_size_half = (unsigned) base_size/3;
	bitwise_image.create(base_size_half,base_size_half);
	for (unsigned i = 0; i < base_size_half; i++) {
		for (unsigned j = 0; j < base_size_half; j++) {
			bitwise_image.setPixel(i, j, sf::Color( 255*j/base_size_half, 255 * ((j + i) / (2 * base_size_half)), 255*i/base_size_half,255));
		}
	}
	wall_tex.loadFromImage(bitwise_image);
	wall_tex.setRepeated(true);
}

wall_gen::~wall_gen()
{
}

void wall_gen::add_wall_single(const sf::Vector2u coord, unsigned len, wall_dir_no dir)
{
	sf::RectangleShape temp;
	temp.setPosition(coord.x*base_size, coord.y*base_size);
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
	temp.setTexture(&wall_tex); 
	temp.setTextureRect({0,0,(int)temp.getLocalBounds().width,(int) temp.getLocalBounds().height});
	walls.push_back(temp);
}

void wall_gen::add_wall_chain(const std::vector<sf::Vector2u>& points)
{
	sf::Vector2u chain_point = (points.size() > 0) ? points[0] : sf::Vector2u(0u,0u);
	for (int i = 1; i < points.size(); i++) {
		sf::RectangleShape temp;
		temp.setPosition(chain_point.x*base_size, chain_point.y*base_size);
		int temp_x = ((points[i].x - chain_point.x) == 0) ? 1 : points[i].x - chain_point.x;
		if (points[i].x > chain_point.x) { temp_x += 1; }
		int temp_y = ((points[i].y - chain_point.y) == 0) ? 1 : points[i].y - chain_point.y;
		if (points[i].y > chain_point.y) { temp_y += 1; }
		temp.setSize(sf::Vector2f(base_size*temp_x, base_size*temp_y));
		temp.setTexture(&wall_tex);
		temp.setTextureRect({ 0,0,(int)temp.getLocalBounds().width,(int)temp.getLocalBounds().height });
		walls.push_back(temp);
		chain_point = points[i];
	}
}



void wall_gen::render(sf::RenderTarget * target)
{
	for (auto i : this->walls)
	{
		target->draw(i);
	}
}

