#pragma once

#include "../stdafx.h"
#include "../Data.h"

class Obstacle
{

public:

	enum class obstacle_type { Gun = 1, Dragon, Pufferfish, Sprite, Spring, Teleporter }Type;

	Obstacle() {}

	virtual ~Obstacle() {}

	virtual void update(float dt) = 0;
	virtual void render(sf::RenderTarget *target) = 0;
	virtual const bool isCollide(const sf::FloatRect &shape) = 0;
};

