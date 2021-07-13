#include "stdafx.h"
#include "game.h"
#include "level1.h"

void game::InitFonts()
{
	m_context->m_assets->add_font(0, "Fonts/Dosis-Light.otf");
}

void game::InitTextures()
{
	m_context->m_assets->add_texture(asset_holder::group_member_name::OJJAS, 0, "Images/spring.png");
	m_context->m_assets->add_texture(asset_holder::group_member_name::OJJAS, 1, "Images/teleporter.png");
}
void game::InitSounds() {
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS, 0, "Sounds/bounce.flac");
	m_context->m_assets->add_sound_buffer(asset_holder::group_member_name::OJJAS, 1, "Sounds/teleport.flac");
}
game::game()

{
	m_context = std::make_shared<context>();
	m_context->m_window->create(sf::VideoMode(900,600), "TOTM Color game", sf::Style::Close);
	InitTextures();
	InitFonts();
	InitSounds();
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
			m_context->m_assets->clear_sounds();
			m_context->m_states->ProcessStatechange();
			m_context->m_states->Getcurrent()->pollevents();
			m_context->m_states->Getcurrent()->update(dt);
			m_context->m_states->Getcurrent()->render();
	}
}
