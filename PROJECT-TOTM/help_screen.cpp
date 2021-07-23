#include "stdafx.h"
#include "help_screen.h"

help_screen::help_screen(std::shared_ptr<context>& context) :m_context(context)
{
}

help_screen::~help_screen()
{
}

void help_screen::init()
{
	Helpfull_text.setFont(m_context->m_assets->get_font(asset_holder::fonts::DOSIS_REGULAR));
	Helpfull_text.setFillColor(sf::Color(0,255,50,255));
	Helpfull_text.setString("Use WASD for movement and press Enter to select \n"
	"Press P to Pause/Unpause a Level\n"
	"Avoid obstacles such as bats,guns,pufferfishes etc \nUse telporters and springs to your Advantage \n"
	"Win by painting entire level\n\n\n\n\n        Press Esc to exit help menu" );
}

void help_screen::pollevents()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS,asset_holder::ojjas_sounds::BUTTON_BACKWARD);
				m_context->m_states->Popcurrent();
			}

		}

	}
}

void help_screen::update(float & deltatime)
{
}

void help_screen::render()
{
	m_context->m_window->clear();
	m_context->m_window->draw(Helpfull_text);
	m_context->m_window->display();
}
