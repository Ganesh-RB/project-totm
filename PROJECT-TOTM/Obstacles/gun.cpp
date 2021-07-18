#include "../stdafx.h"
#include "gun.h"

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

gun::gun(sf::Vector2u GunPosition, sf::Vector2u TargetPosition)
{
	BASE_SIZE = 30.f;
	this->Type = Obstacle::obstacle_type::Gun;
	this->GunPosition.x = BASE_SIZE * GunPosition.x;		this->GunPosition.y = BASE_SIZE * GunPosition.y;
	this->TargetPosition.x = BASE_SIZE * TargetPosition.x;		this->TargetPosition.y = BASE_SIZE * TargetPosition.y;
	this->counter = 0;

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
	this->GunPosition.x = BASE_SIZE * GunPosition.x;		this->GunPosition.y = BASE_SIZE * GunPosition.y;
	Gunshape.setPosition(GunPosition);
}

void gun::setTargetPosition(sf::Vector2f TargetPosition)
{
	this->TargetPosition.x = BASE_SIZE * TargetPosition.x;		this->TargetPosition.y = BASE_SIZE * TargetPosition.y;
	initBullet();
}

void gun::update(const float dt)
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

	float dist = fabs((TargetPosition.x - GunPosition.x + TargetPosition.y - GunPosition.y + 300.f)/300.f);
	
	
	if (counter < dist )
		counter+=dt;
	if (counter >= dist )
	{
		counter = 0;
		Bullets.push_back(Bullet);
	}
	

	// move

	for (size_t i = 0; i < Bullets.size(); i++)
	{
		float speed = 300.f; // 5.f at frame rate 60

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

void gun::render(sf::RenderTarget* window)
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

void gun::read(std::ifstream & fin, Data &data, size_t & size)
{
	unsigned temp_var1, temp_var2, temp_var3, temp_var4;

	for (size_t i = 0; i < size; i++)
	{
		fin >> temp_var1 >> temp_var2;
		fin >> temp_var3 >> temp_var4;

		data.gun_arg.push_back(std::pair< sf::Vector2u, sf::Vector2u >(sf::Vector2u(temp_var1, temp_var2), sf::Vector2u(temp_var3, temp_var4)));
	}


}
