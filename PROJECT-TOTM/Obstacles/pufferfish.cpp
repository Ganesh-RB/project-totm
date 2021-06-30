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
	PlayerSize = sf::Vector2f(30.f, 30.f);
	this->FishPosition2.x = Fishposition.x*PlayerSize.x - PlayerSize.x;
	this->FishPosition2.y = Fishposition.y*PlayerSize.y - PlayerSize.y;
	this->FishPosition1.x = Fishposition.x*PlayerSize.x;
	this->FishPosition1.y = Fishposition.y*PlayerSize.y;
	this->FishPosition.x = Fishposition.x*PlayerSize.x;
	this->FishPosition.y = Fishposition.y*PlayerSize.y;
	FishSize = PlayerSize;
	Fish1();
	t = 0.f;
}


pufferfish::~pufferfish()
{
}


void pufferfish::Updatefish(float dt, float u)
{
	t += dt;
	int i = (int(t / u));
	if (i < 13) {
		this->FishPosition.x = this->FishPosition1.x - i * 2.5f; this->FishPosition.y = this->FishPosition1.y - i * 2.5f;
		this->FishSize.x = PlayerSize.x + i * 5.f; this->FishSize.y = PlayerSize.y + i * 5.f;
		Fish1();
	}
	if (i > 12 && i < 25)
	{
		this->FishPosition.x = this->FishPosition2.x + (i - 12)*2.5f; this->FishPosition.y = this->FishPosition2.y + (i - 12)*2.5f;
		this->FishSize.x = PlayerSize.x*3.f - (i - 12)*5.f; this->FishSize.y = PlayerSize.y*3.f - (i - 12)*5.f;
		Fish1();
	}
	if (i < 50 && i>24)
	{
		this->FishPosition.x = FishPosition1.x;
		this->FishPosition.y = FishPosition1.y;
		FishSize = PlayerSize;
		Fish1();
	}
	if (i >= 50) {
		t = 0.f;
	}
}
const bool pufferfish::isCollide(const sf::FloatRect & shape)
{
	if (this->FishSize != PlayerSize)
	{
		if (Fish.getGlobalBounds().intersects(shape))
			return true;
		else
			return false;
	}
}

void pufferfish::Render_fish(sf::RenderWindow * window)
{
	window->draw(Fish);
}