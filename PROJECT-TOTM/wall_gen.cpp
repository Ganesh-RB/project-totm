#include "wall_gen.h"
wall_gen::wall_gen(sf::Color _color, float _base_size)
{
	wall_colour = _color;
	base_size = _base_size;
	chain_point = sf::Vector2u(0U, 0U);
	chain_start = true;
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

void wall_gen::add_wall_single(float x_coord, float y_coord, float len, wall_dir_no dir)
{
	sf::RectangleShape temp;
	//temp.setFillColor(wall_colour);
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
	temp.setTexture(&wall_tex); 
	temp.setTextureRect({0,0,(int)temp.getLocalBounds().width,(int) temp.getLocalBounds().height});
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

