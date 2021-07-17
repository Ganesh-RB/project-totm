#include "..\stdafx.h"
#include "pufferfish.h"


void pufferfish::Fish1()
{

	Fish.setSize(FishSize);
	Fish.setPosition(FishPosition);
	Fish.setFillColor(sf::Color::Red);
}


pufferfish::pufferfish(sf::Vector2u Fishposition)
{
	this->Type = Obstacle::obstacle_type::Pufferfish;
	BASE_SIZE = 30.f;
	this->FishPosition2.x = Fishposition.x*BASE_SIZE - BASE_SIZE;
	this->FishPosition2.y = Fishposition.y*BASE_SIZE - BASE_SIZE;
	this->FishPosition1.x = Fishposition.x*BASE_SIZE;
	this->FishPosition1.y = Fishposition.y*BASE_SIZE;
	this->FishPosition.x = Fishposition.x*BASE_SIZE;
	this->FishPosition.y = Fishposition.y*BASE_SIZE;
	FishSize = sf::Vector2f(BASE_SIZE,BASE_SIZE);
	Fish1();
	t = 0.f;
}


pufferfish::~pufferfish()
{
}


void pufferfish::update(float dt, float u)
{
	t += dt;
	int i = (int(t / u));
	if (i < 13) {
		this->FishPosition.x = this->FishPosition1.x - i * 2.5f; this->FishPosition.y = this->FishPosition1.y - i * 2.5f;
		this->FishSize.x = BASE_SIZE + i * 5.f; this->FishSize.y = BASE_SIZE + i * 5.f;
		Fish1();
	}
	if (i > 12 && i < 25)
	{
		this->FishPosition.x = this->FishPosition2.x + (i - 12)*2.5f; this->FishPosition.y = this->FishPosition2.y + (i - 12)*2.5f;
		this->FishSize.x = BASE_SIZE*3.f - (i - 12)*5.f; this->FishSize.y = BASE_SIZE*3.f - (i - 12)*5.f;
		Fish1();
	}
	if (i < 50 && i>24)
	{
		this->FishPosition.x = FishPosition1.x;
		this->FishPosition.y = FishPosition1.y;
		FishSize = sf::Vector2f(BASE_SIZE,BASE_SIZE);
		Fish1();
	}
	if (i >= 50) {
		t = 0.f;
	}
}

void pufferfish::update(float dt)
{
	float u = 0.1f;
	t += dt;
	int i = (int(t / u));
	if (i < 13) {
		this->FishPosition.x = this->FishPosition1.x - i * 2.5f; this->FishPosition.y = this->FishPosition1.y - i * 2.5f;
		this->FishSize.x = BASE_SIZE + i * 5.f; this->FishSize.y = BASE_SIZE + i * 5.f;
		Fish1();
	}
	if (i > 12 && i < 25)
	{
		this->FishPosition.x = this->FishPosition2.x + (i - 12)*2.5f; this->FishPosition.y = this->FishPosition2.y + (i - 12)*2.5f;
		this->FishSize.x = BASE_SIZE*3.f - (i - 12)*5.f; this->FishSize.y = BASE_SIZE*3.f - (i - 12)*5.f;
		Fish1();
	}
	if (i < 50 && i>24)
	{
		this->FishPosition.x = FishPosition1.x;
		this->FishPosition.y = FishPosition1.y;
		FishSize = sf::Vector2f(BASE_SIZE,BASE_SIZE);
		Fish1();
	}
	if (i >= 50) {
		t = 0.f;
	}
}

const bool pufferfish::isCollide(const sf::FloatRect & shape)
{
	if (this->FishSize != sf::Vector2f(BASE_SIZE,BASE_SIZE))
	{
		if (Fish.getGlobalBounds().intersects(shape))
			return true;
		else
			return false;
	}
	else {return false;}
}

void pufferfish::render(sf::RenderTarget * window)
{
	window->draw(Fish);
}

void pufferfish::read(std::ifstream & fin, Data &data, size_t & size)
{
	unsigned temp_var1, temp_var2;
	char c_var1;

	for (size_t i = 0; i < size; i++)
	{
		fin >> temp_var1 >> temp_var2;

		data.Pfish_arg.push_back(sf::Vector2u(temp_var1, temp_var2));
	}

	fin >> c_var1;

}