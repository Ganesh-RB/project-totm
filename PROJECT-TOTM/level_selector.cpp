#include "stdafx.h"
#include "level_selector.h"


level_selector::level_selector(std::shared_ptr<context>& context):m_context(context)
{
}

level_selector::~level_selector()
{
}

void level_selector::init()
{
	title_font = &m_context->m_assets->get_font(asset_holder::fonts::DOSIS_EXTRABOLD);
	body_font = &m_context->m_assets->get_font(asset_holder::fonts::DOSIS_BOLD);
	title_text.setFont(*title_font);
	level_text.setFont(*body_font);
	level_count_text.setFont(*body_font);
	title_text.setCharacterSize(60);
	level_text.setCharacterSize(40);
	level_count_text.setCharacterSize(40);
	title_text.setString("Select Level");
	title_text.setOrigin(title_text.getLocalBounds().width / 2.f, 0);
	title_text.setPosition(m_context->m_window->getSize().x / 2.f, 0.f);
	level_text.setString("Level");
	level_text.setPosition(m_context->m_window->getSize().x / 3.f, m_context->m_window->getSize().y / 2.f);
	level_count_text.setPosition(m_context->m_window->getSize().x / 3.f + 100.f, m_context->m_window->getSize().y / 2.f);
	level_count_text.setString(std::to_string(level_number));
	uparrow.setPointCount(3);
	downarrow.setPointCount(3);
	uparrow.setRadius(10.f);
	downarrow.setRadius(10.f);
	uparrow.setFillColor(sf::Color(0,255,0,255));
	downarrow.setFillColor(sf::Color(0, 255, 0, 255));
	uparrow.setPosition(m_context->m_window->getSize().x / 3.f + 100.f, m_context->m_window->getSize().y / 2.f - 10.f);
	downarrow.setPosition(m_context->m_window->getSize().x / 3.f + 120.f, m_context->m_window->getSize().y / 2.f + 60.f);
	downarrow.setRotation(180.f);
	level_count_text.setFillColor(sf::Color::Red);

}

void level_selector::pollevents()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				if (level_number > 1) {
					level_number -= 1;
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BEEP);
				}
				else {
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_BACKWARD);
				}
				break;
			case sf::Keyboard::S:
				if (level_number < NUMBER_OF_LEVELS) {
					level_number += 1;
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BEEP);
				}
				else {
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_BACKWARD);
				}
				break;
			case sf::Keyboard::Enter:
				(*m_context->m_level_no.get())= level_number;
				m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD);
				m_context->m_states->Add(std::make_unique<Level>(m_context), true);
				break;
			default:
				break;

			}
		}

	}
}

void level_selector::update(float & dt)
{
	level_count_text.setString(std::to_string(level_number));
	uparrow.setFillColor(sf::Color(0, 255, 0, 255));
	downarrow.setFillColor(sf::Color(0, 255, 0, 255));
	if (level_number == 1) { uparrow.setFillColor(sf::Color(0, 255, 0, 130)); }
	if (level_number == NUMBER_OF_LEVELS) { downarrow.setFillColor(sf::Color(0, 255, 0, 130)); }
}

void level_selector::render()
{
	m_context->m_window->clear();
	m_context->m_window->draw(title_text);
	m_context->m_window->draw(uparrow);
	m_context->m_window->draw(downarrow);
	m_context->m_window->draw(level_text);
	m_context->m_window->draw(level_count_text);


	m_context->m_window->display();
}
