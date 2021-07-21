#include "..\stdafx.h"
#include "Dragon.h"

void Dragon::initVariable()
{
	this->clock.restart();
	this->isStuck = 0;
	if (!this->texture.loadFromFile("Images/Dragon.png"))
		std::cout << "Images/Dragon file not loaded\n";
	this->CurrentFrame = sf::IntRect(0, 0, 30, 30);

	this->moving_dir = this->dir.first;
}

void Dragon::initDirection()
{
	if (FinalPosition.x > InitialPosition.x)
	{
		dir.first = direction::Right;
		dir.second = sf::Vector2f(1.f, 0.f);
	}
	else if (FinalPosition.x < InitialPosition.x)
	{
		dir.first = direction::Left;
		dir.second = sf::Vector2f(-1.f, 0.f);
	}

	if (FinalPosition.y > InitialPosition.y)
	{
		dir.first = direction::Down;
		dir.second = sf::Vector2f(0.f, 1.f);
	}
	else if (FinalPosition.y < InitialPosition.y)
	{
		dir.first = direction::Up;
		dir.second = sf::Vector2f(0.f, -1.f);
	}
}

void Dragon::initSprite()
{
	this->dragonShape.setPosition(this->InitialPosition);
	this->dragonShape.setTexture(this->texture);
	this->dragonShape.setTextureRect(this->CurrentFrame);

}

void Dragon::update_movement(float moving_speed, float dt)
{
	if (moving_dir == this->dir.first)
		dragonShape.move(this->dir.second*(moving_speed*dt*60.f));
	else
		dragonShape.move(this->dir.second*(-moving_speed * dt*60.f));

}

void Dragon::fly()
{
	if (this->clock.getElapsedTime().asSeconds() >= 0.2f)
	{
		this->CurrentFrame.left += 30;
		if (this->CurrentFrame.left >= 90)
			this->CurrentFrame.left = 0;

		this->clock.restart();
		this->dragonShape.setTextureRect(this->CurrentFrame);
	}

}

Dragon::Dragon(sf::Vector2u InitialPosition, sf::Vector2u FinalPosition)
{
	this->Type = Obstacle::obstacle_type::Dragon;

	this->InitialPosition.x = InitialPosition.x * BASE_SIZE;		
	this->InitialPosition.y = BASE_SIZE * InitialPosition.y;
	this->FinalPosition.x = FinalPosition.x * BASE_SIZE;		
	this->FinalPosition.y = BASE_SIZE * FinalPosition.y;

	this->initDirection();
	this->initVariable();
	this->initSprite();

}

Dragon::~Dragon()
{
}

void Dragon::update(float dt)
{

	fly();

	if (isStuck <= 200)
		isStuck++;
	else
	{
		isStuck++;


		switch (this->dir.first)
		{

		case direction::Right:
			if (dragonShape.getPosition().x <= FinalPosition.x	&&  dragonShape.getPosition().x >= InitialPosition.x)
			{
				update_movement(1.f, dt);
			}
			else
			{
				isStuck = 0;
				moving_dir = direction(-moving_dir);
				update_movement(3.f, dt);
			}
			break;

		case direction::Left:
			if (dragonShape.getPosition().x >= FinalPosition.x	&&  dragonShape.getPosition().x <= InitialPosition.x)
			{
				update_movement(1.f, dt);
			}
			else
			{
				isStuck = 0;
				moving_dir = direction(-moving_dir);
				update_movement(3.f, dt);
			}
			break;
		case direction::Up:
			if (dragonShape.getPosition().y >= FinalPosition.y	&&  dragonShape.getPosition().y <= InitialPosition.y)
			{
				update_movement(1.f, dt);
			}
			else
			{
				isStuck = 0;
				moving_dir = direction(-moving_dir);
				update_movement(3.f, dt);
			}
			break;
		case direction::Down:
			if (dragonShape.getPosition().y <= FinalPosition.y	&&  dragonShape.getPosition().y >= InitialPosition.y)
			{
				update_movement(1.f, dt);
			}
			else
			{
				isStuck = 0;
				moving_dir = direction(-moving_dir);
				update_movement(3.f, dt);
			}
			break;
		default:
			break;
		}
	}
}

void Dragon::render(sf::RenderTarget * target)
{

	target->draw(this->dragonShape);
}


const bool Dragon::isCollide(const sf::FloatRect& shape)
{
	return dragonShape.getGlobalBounds().intersects(shape);
}

void Dragon::read(std::ifstream & fin, Data &data, size_t & size)
{
	unsigned temp_var1, temp_var2, temp_var3, temp_var4;

	for (size_t i = 0; i < size; i++)
	{
		fin >> temp_var1 >> temp_var2;
		fin >> temp_var3 >> temp_var4;

		data.dragon_arg.push_back(std::pair< sf::Vector2u, sf::Vector2u >(sf::Vector2u(temp_var1, temp_var2), sf::Vector2u(temp_var3, temp_var4)));
	}


}