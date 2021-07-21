#include "../stdafx.h"
#include "gun.h"

void gun::initBullet()
{
	isMove = true;
	crabOpen = 0;

	this->clock2_bullet.restart();
	if (!this->bullettexture.loadFromFile("Images/bullet.png"))
		std::cout << "Images/Dragon file not loaded\n";
	this->bulletCurrentFrame = sf::IntRect(0, 0, 30, 30);

}

void gun::initGunShape()
{
	this->clock1_gun.restart();
	if (!this->guntexture.loadFromFile("Images/Sprite.png"))
		std::cout << "Images/Dragon file not loaded\n";
	this->gunCurrentFrame = sf::IntRect(0, 0, 30, 30);
	this->gunbackground.setSize(sf::Vector2f(BASE_SIZE, BASE_SIZE));
	this->gunbackground.setFillColor(sf::Color(0, 0, 0, 180));
	this->gunbackground.setPosition(GunPosition);
}

void gun::initSprite()
{
	this->bulletShape.setPosition(GunPosition);
	this->bulletShape.setTexture(bullettexture);
	this->bulletShape.setTextureRect(bulletCurrentFrame);
	this->bulletShape.setOrigin(BASE_SIZE / 2, BASE_SIZE / 2);
	this->bulletShape.setPosition(GunPosition.x + BASE_SIZE / 2, GunPosition.y + BASE_SIZE / 2);

	this->gunShape.setPosition(GunPosition);
	this->gunShape.setTexture(guntexture);
	this->gunShape.setTextureRect(gunCurrentFrame);
	this->gunShape.setOrigin(BASE_SIZE / 2, BASE_SIZE / 2);
	this->gunShape.setPosition(GunPosition.x + BASE_SIZE / 2, GunPosition.y + BASE_SIZE / 2);

	switch (dir)
	{
	case gun::direction::Left:
		this->gunShape.setRotation(270.f);
		this->bulletShape.setRotation(90.f);
		break;
	case gun::direction::Down:
		this->gunShape.setRotation(180.f);
		this->bulletShape.setRotation(180.f);
		break;
	case gun::direction::Up:
		break;
	case gun::direction::Right:
		this->gunShape.setRotation(90.f);
		this->bulletShape.setRotation(270.f);
		break;
	default:
		break;
	}
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

void gun::Animation(float dt)
{
	if (this->clock1_gun.getElapsedTime().asSeconds() >= 0.2f)
	{

		switch (crabOpen)
		{
		case 0:
			this->gunCurrentFrame.left = 0;
			break;
		case 1:
			this->gunCurrentFrame.left += 30;
			if (this->gunCurrentFrame.left >= 60)
				crabOpen = -1;
			break;
		case -1:
			this->gunCurrentFrame.left -= 30;
			if (this->gunCurrentFrame.left <= 0)
				crabOpen = 0;
			break;
		default:
			break;
		}

		this->clock1_gun.restart();
		this->gunShape.setTextureRect(this->gunCurrentFrame);
	}

	if (this->clock2_bullet.getElapsedTime().asSeconds() >= 0.2f)
	{
		if (this->bulletCurrentFrame.left == 0 && this->bulletCurrentFrame.top == 0)
			this->bulletCurrentFrame.left += 30;
		else if (this->bulletCurrentFrame.left == 30 && this->bulletCurrentFrame.top == 0)
			this->bulletCurrentFrame.top += 30;
		else if (this->bulletCurrentFrame.left == 30 && this->bulletCurrentFrame.top == 30)
			this->bulletCurrentFrame.left -= 30;
		else if (this->bulletCurrentFrame.left == 0 && this->bulletCurrentFrame.top == 30)
			this->bulletCurrentFrame.top -= 30;

		this->clock2_bullet.restart();
		this->bulletShape.setTextureRect(this->bulletCurrentFrame);
	}
	this->bulletShape.setScale(BASE_SIZE / bulletShape.getGlobalBounds().width, BASE_SIZE / bulletShape.getGlobalBounds().height);

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
	initSprite();

}

gun::~gun()
{

}

void gun::setGunPosition(sf::Vector2f GunPosition)
{
	this->GunPosition.x = BASE_SIZE * GunPosition.x;		this->GunPosition.y = BASE_SIZE * GunPosition.y;
	gunShape.setPosition(GunPosition);
}

void gun::setTargetPosition(sf::Vector2f TargetPosition)
{
	this->TargetPosition.x = BASE_SIZE * TargetPosition.x;		this->TargetPosition.y = BASE_SIZE * TargetPosition.y;
	initBullet();
}

void gun::update(const float dt)
{
	this->Animation(dt);
	//check erase

	switch (dir)
	{
	case direction::Right:
		if (bulletShape.getPosition().x >= TargetPosition.x)
		{
			this->bulletShape.setPosition(GunPosition.x + BASE_SIZE / 2, GunPosition.y + BASE_SIZE / 2);
			isMove = false;
		}
		break;
	case direction::Left:
		if (bulletShape.getPosition().x <= TargetPosition.x)
		{
			this->bulletShape.setPosition(GunPosition.x + BASE_SIZE / 2, GunPosition.y + BASE_SIZE / 2);
			isMove = false;
		}
		break;
	case direction::Down:
		if (bulletShape.getPosition().y >= TargetPosition.y)
		{
			this->bulletShape.setPosition(GunPosition.x + BASE_SIZE / 2, GunPosition.y + BASE_SIZE / 2);
			isMove = false;
		}
		break;
	case direction::Up:
		if (bulletShape.getPosition().y <= TargetPosition.y)
		{
			this->bulletShape.setPosition(GunPosition.x + BASE_SIZE / 2, GunPosition.y + BASE_SIZE / 2);
			isMove = false;
		}
		break;

	}

	//update new bullets

	float dist = fabs((TargetPosition.x - GunPosition.x + TargetPosition.y - GunPosition.y + 300.f)/300.f);
	
	
	if (counter < 2*dist )
		counter+=dt;
	if (counter >= 2*dist )
	{
		counter = 0;
		isMove = true;
		crabOpen = 1;
	}
	

	// move

	
	float speed = 200.f; // 5.f at frame rate 60
	if (isMove)
	{
		switch (dir)
		{
		case direction::Right:
			bulletShape.move(dt * speed, 0.f);
			break;
		case direction::Left:
			bulletShape.move(-speed * dt, 0.f);
			break;
		case direction::Down:
			bulletShape.move(0.f, dt * speed);
			break;
		case direction::Up:
			bulletShape.move(0.f, -dt * speed);
			break;
		}
	}

}

void gun::render(sf::RenderTarget* window)
{
	window->draw(gunbackground);
	window->draw(bulletShape);
	window->draw(gunShape);

}

const sf::Vector2f gun::getGunPosition()
{
	return sf::Vector2f(gunShape.getPosition());
}

const sf::Vector2f gun::getTargetPosition()
{
	return sf::Vector2f(TargetPosition);
}

const bool gun::isCollide(const sf::FloatRect &shape)
{
	if (bulletShape.getGlobalBounds().intersects(shape))
		return true;
	
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
