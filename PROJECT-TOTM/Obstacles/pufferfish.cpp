#include "..\stdafx.h"
#include "pufferfish.h"


void pufferfish::Fish1()
{

	Fish.setSize(FishSize);
	Fish.setPosition(FishPosition);
	Fish.setFillColor(sf::Color::Black);
}

void pufferfish::Anim(float dt,bool is_expanding)
{
	if (is_expanding) {
		pufferfish_sprite.setTextureRect(display_frames[3]);
		pufferfish_sprite.setScale(sf::Vector2f((BASE_SIZE*FishSize.x) / 900.f, (BASE_SIZE*FishSize.y) / 900.f));
		pufferfish_sprite.setPosition(FishPosition);
	}
	else {
		timer_anim += 180.f * anim_dir*dt;
		if (timer_anim < 0.f) { anim_dir = 1; }
		if (timer_anim > 60.f) { anim_dir = -1; }
		if (timer_anim > 40.f) { pufferfish_sprite.setTextureRect(display_frames[2]); }
		else if (timer_anim > 20.f) { pufferfish_sprite.setTextureRect(display_frames[1]); }
		else { pufferfish_sprite.setTextureRect(display_frames[0]); }
		pufferfish_sprite.setScale(sf::Vector2f(BASE_SIZE/25.f, BASE_SIZE/25.f));
		pufferfish_sprite.setPosition(FishPosition-sf::Vector2f(0.1*BASE_SIZE,0.1*BASE_SIZE));
	}

}


pufferfish::pufferfish(sf::Vector2u Fishposition,asset_holder* assets):m_assets(*assets)
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
	timer = 0.f;
	for (int i = 0; i < 4; i++) {
		display_frames[i]=sf::IntRect(30*i,0,30,30);
	}
	pufferfish_sprite.setTexture(m_assets.get_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::PUFFERFISH));
	timer_anim = 0.f;
	anim_dir = 1.f;
}


pufferfish::~pufferfish()
{
}

void pufferfish::update(float dt)
{
	float u = 0.1f;
	timer += dt;
	int i = (int(timer / u));
	if (i < 13) {
		this->FishPosition.x = this->FishPosition1.x - i * 2.5f; this->FishPosition.y = this->FishPosition1.y - i * 2.5f;
		this->FishSize.x = BASE_SIZE + i * 5.f; this->FishSize.y = BASE_SIZE + i * 5.f;
		Fish1();
		Anim(dt, true);
	}
	if (i > 12 && i < 25)
	{
		this->FishPosition.x = this->FishPosition2.x + (i - 12)*2.5f; this->FishPosition.y = this->FishPosition2.y + (i - 12)*2.5f;
		this->FishSize.x = BASE_SIZE*3.f - (i - 12)*5.f; this->FishSize.y = BASE_SIZE*3.f - (i - 12)*5.f;
		Fish1();
		Anim(dt, true);
	}
	if (i < 50 && i>24)
	{
		this->FishPosition.x = FishPosition1.x;
		this->FishPosition.y = FishPosition1.y;
		FishSize = sf::Vector2f(BASE_SIZE,BASE_SIZE);
		Fish1();
		Anim(dt, false);
	}
	if (i >= 50) {
		timer = 0.f;
		m_assets.play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::STRETCH);
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
	if (FishSize.x <= BASE_SIZE * 1.2f) {
		window->draw(Fish);
	}
	window->draw(pufferfish_sprite);
}

void pufferfish::read(std::ifstream & fin, Data &data, size_t & size)
{
	unsigned temp_var1, temp_var2;

	for (size_t i = 0; i < size; i++)
	{
		fin >> temp_var1 >> temp_var2;

		data.Pfish_arg.push_back(sf::Vector2u(temp_var1, temp_var2));
	}


}