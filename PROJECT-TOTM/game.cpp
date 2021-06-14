#include "game.h"
#include "level1.h"

game::game() 

{
	m_context = std::make_shared<context>();
	m_context->m_window->create(sf::VideoMode(900,600), "TOTM Color game", sf::Style::Close);
	m_context->m_states->Add(std::make_unique<level1>(m_context));
	// Should only call main menu state,to be done
}

game::~game()
{
}

void game::run()
{
	sf::Clock timer;
	float dt;
	while (m_context->m_window->isOpen())
	{
		    dt = timer.restart().asSeconds();
			m_context->m_states->ProcessStatechange();
			m_context->m_states->Getcurrent()->pollevents();
			m_context->m_states->Getcurrent()->update(dt);
			m_context->m_states->Getcurrent()->render();
	}
}
