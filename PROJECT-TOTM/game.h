#pragma once
#include <memory>
#include <SFML\Graphics.hpp>
#include "stateman.h"


struct context
{
	std::unique_ptr<stateman> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;

	context()
	{
		m_states = std::make_unique<stateman>();
		m_window = std::make_unique<sf::RenderWindow>();
	}
};

class game
{
private:
	std::shared_ptr<context> m_context;

public:
	game();
	~game();

	void run();
};

