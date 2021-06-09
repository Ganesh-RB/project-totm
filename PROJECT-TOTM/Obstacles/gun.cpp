#include "gun.h"
#include <iostream>
#include <math.h>
#include <cstdlib>

void gun::initBullet()
{
	Bullet.setPosition(GunPosition);
	Bullet.setPointCount(5);
	switch (dir)
	{
	case direction::Right:
		Bullet.setPoint(0, sf::Vector2f(10.f, 10.f));
		Bullet.setPoint(1, sf::Vector2f(20.f, 10.f));
		Bullet.setPoint(2, sf::Vector2f(25.f, 15.f));
		Bullet.setPoint(3, sf::Vector2f(20.f, 20.f));
		Bullet.setPoint(4, sf::Vector2f(10.f, 20.f));
		break;
	case direction::Left:
		Bullet.setPoint(0, sf::Vector2f(5.f, 15.f));
		Bullet.setPoint(1, sf::Vector2f(10.f, 10.f));
		Bullet.setPoint(2, sf::Vector2f(20.f, 10.f));
		Bullet.setPoint(3, sf::Vector2f(20.f, 20.f));
		Bullet.setPoint(4, sf::Vector2f(10.f, 20.f));
		break;
	case direction::Down:
		Bullet.setPoint(0, sf::Vector2f(10.f, 10.f));
		Bullet.setPoint(1, sf::Vector2f(20.f, 10.f));
		Bullet.setPoint(2, sf::Vector2f(20.f, 20.f));
		Bullet.setPoint(3, sf::Vector2f(15.f, 25.f));
		Bullet.setPoint(4, sf::Vector2f(10.f, 20.f));
		break;
	case direction::Up:
		Bullet.setPoint(0, sf::Vector2f(15.f, 5.f));
		Bullet.setPoint(1, sf::Vector2f(20.f, 10.f));
		Bullet.setPoint(2, sf::Vector2f(20.f, 20.f));
		Bullet.setPoint(3, sf::Vector2f(10.f, 20.f));
		Bullet.setPoint(4, sf::Vector2f(10.f, 10.f));
		break;
	}

	Bullet.setOutlineColor(sf::Color::Blue);
	Bullet.setOutlineThickness(1.5f);
}

void gun::initGunShape()
{
	Gunshape.setSize(sf::Vector2f(30.f, 30.f));
	Gunshape.setPosition(GunPosition);
	Gunshape.setFillColor(sf::Color::Magenta);
}

void gun::initDirection()
{
	if (TargetPosition.x > GunPosition.x)
		dir = direction::Right;
	else if (TargetPosition.x < GunPosition.x)
		dir = direction::Left;

	if (TargetPosition.y > GunPosition.y)
		dir = direction::Down;
	else if (TargetPosition.y < GunPosition.y)
		dir = direction::Up;
}

gun::gun(sf::Vector2u GunPosition, sf::Vector2u TargetPosition, gunType Type = gunType::Simple)
{
	this->GunPosition.x = PlayerSize.x * GunPosition.x;		this->GunPosition.y = PlayerSize.x * GunPosition.y;
	this->TargetPosition.x = PlayerSize.x * TargetPosition.x;		this->TargetPosition.y = PlayerSize.y * TargetPosition.y;
	this->Type = Type;
	this->counter = 0.f;

	initGunShape();
	initDirection();
	initBullet();

	(this->Bullets).push_back(this->Bullet);
}

gun::~gun()
{
}

void gun::setGunPosition(sf::Vector2f GunPosition)
{
	this->GunPosition.x = PlayerSize.x * GunPosition.x;		this->GunPosition.y = PlayerSize.x * GunPosition.y;
	Gunshape.setPosition(GunPosition);
}

void gun::setTargetPosition(sf::Vector2f TargetPosition)
{
	this->TargetPosition.x = PlayerSize.x * TargetPosition.x;		this->TargetPosition.y = PlayerSize.y * TargetPosition.y;
	initBullet();
}

void gun::gunfire(const float dt)
{
	//check erase
	for (size_t i = 0; i < Bullets.size(); i++)
	{

		switch (dir)
		{
		case direction::Right:
			if (Bullets[i].getPosition().x >= TargetPosition.x)
				Bullets.erase(Bullets.begin() + i);
			break;
		case direction::Left:
			if (Bullets[i].getPosition().x <= TargetPosition.x)
				Bullets.erase(Bullets.begin() + i);
			break;
		case direction::Down:
			if (Bullets[i].getPosition().y >= TargetPosition.y)
				Bullets.erase(Bullets.begin() + i);
			break;
		case direction::Up:
			if (Bullets[i].getPosition().y <= TargetPosition.y)
				Bullets.erase(Bullets.begin() + i);
			break;

		}
	}

	//update new bullets

	int dist = int(fabs((TargetPosition.x - GunPosition.x + TargetPosition.y - GunPosition.y) / (dt*300.f)));

	if (Type == gunType::Simple)
	{
		if (counter < 120.f)
			counter+= 1*dt*60;
		if (counter >= 120.f)
		{
			counter = 0.f;
			Bullets.push_back(Bullet);
		}
	}
	if (Type == gunType::Probablistic)
	{
		int c = (rand() % int(100000 / (dt*dist)));
		if (c < 10)
		{
			std::cout << "hello    : " << c << "  :    " << Bullets.size() << std::endl;
			Bullets.push_back(Bullet);
		}

	}


	// move

	for (size_t i = 0; i < Bullets.size(); i++)
	{
		float speed = 300.f; // = 5.f at frame rate 60

		switch (dir)
		{
		case direction::Right:
			Bullets[i].move(dt * speed, 0.f);
			break;
		case direction::Left:
			Bullets[i].move(-speed * dt, 0.f);
			break;
		case direction::Down:
			Bullets[i].move(0.f, dt * speed);
			break;
		case direction::Up:
			Bullets[i].move(0.f, -dt * speed);
			break;

		}

	}

}

void gun::Render_gun(sf::RenderWindow* window)
{

	for (size_t j = 0; j < Bullets.size(); j++)
	{
		window->draw(Bullets[j]);
	}

	window->draw(Gunshape);

}

const sf::Vector2f gun::getGunPosition()
{
	return sf::Vector2f(Gunshape.getPosition());
}

const sf::Vector2f gun::getTargetPosition()
{
	return sf::Vector2f(TargetPosition);
}

const bool gun::isCollide(const sf::FloatRect &shape)
{
	for (size_t i = 0; i < Bullets.size(); i++)
	{
		if (Bullets[i].getGlobalBounds().intersects(shape))
			return true;
	}
	return false;
}
