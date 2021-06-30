#include "..\stdafx.h"
#include "Dragon.h"

void Dragon::initVariable()
{
	this->clock.restart();
	if (!this->texture.loadFromFile("Images/Dragon.png"))
		std::cout << "Images/Dragon file not loaded\n";
	this->CurrentFrame = sf::IntRect(0, 0, 44, 44);
	//this->CurrentFrame = sf::IntRect(0, 0, texture.getSize().x/4, texture.getSize().y);

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
	this->dragonShape.setScale(PlayerSize / dragonShape.getLocalBounds().width, PlayerSize / dragonShape.getLocalBounds().height);

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
		this->CurrentFrame.left += 44;
		if (this->CurrentFrame.left >= 132)
			this->CurrentFrame.left = 0.f;

		this->clock.restart();
		this->dragonShape.setTextureRect(this->CurrentFrame);
		this->dragonShape.setScale(PlayerSize / dragonShape.getLocalBounds().width, PlayerSize / dragonShape.getLocalBounds().height);
	}

}

Dragon::Dragon(sf::Vector2u InitialPosition, sf::Vector2u FinalPosition)
{

	this->InitialPosition.x = InitialPosition.x * PlayerSize;		
	this->InitialPosition.y = PlayerSize * InitialPosition.y;
	this->FinalPosition.x = FinalPosition.x * PlayerSize;		
	this->FinalPosition.y = PlayerSize * FinalPosition.y;

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


	switch (this->dir.first)
	{

	case direction::Right:
		if (dragonShape.getPosition().x <= FinalPosition.x	&&  dragonShape.getPosition().x >= InitialPosition.x)
		{
			update_movement(1.f, dt);
		}
		else
		{
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
			moving_dir = direction(-moving_dir);
			update_movement(3.f, dt);
		}
		break;
	default:
		break;
	}

}

void Dragon::render(sf::RenderTarget * target)
{

	target->draw(this->dragonShape);
}


bool Dragon::isCollide(sf::FloatRect shape)
{
	return dragonShape.getGlobalBounds().intersects(shape);
}
