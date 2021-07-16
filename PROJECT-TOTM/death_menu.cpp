#include "stdafx.h"
#include "death_menu.h"

death_menu::death_menu(std::shared_ptr<context>& context) :gen_menu(context)
{
}

death_menu::~death_menu()
{
}

void death_menu::variable_init()
{
	number_of_options = 3;
	for (int i = 0; i < number_of_options; i++) {
		options.emplace_back(sf::Text());
	}
	menu_title.setFillColor(sf::Color::Green);
	color_text[0] = sf::Color::White;
	color_text[1] = sf::Color::Red;
	menu_title.setString("YOU DIED");
	options[0].setString("Restart");
	options[1].setString("Main Menu");
	options[2].setString("Exit");
	title_font = &m_context->m_assets->get_font(asset_holder::fonts::DOSIS_EXTRABOLD);
	option_font = &m_context->m_assets->get_font(asset_holder::fonts::DOSIS_BOLD);
}

void death_menu::pollevents()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::W:
				if (option_no[0] > 0) {
					option_no[0] -= 1;
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BEEP);
				}
				break;
			case sf::Keyboard::S:
				if (option_no[0] < number_of_options - 1) {
					option_no[0] += 1;
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BEEP);
				}
				break;
			case sf::Keyboard::Enter:
				switch (option_no[0]) {
				case 0:
					m_context->m_states->Add(std::make_unique<level1>(m_context), true);
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD);
					break;
				case 1:
					// add main menu here
					//m_context->m_states->Add(std::make_unique<main_menu>(m_context),true);
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_BACKWARD);
					break;
				case 2:
					m_context->m_window->close();
					break;
				default:
					printf("ERROR::PAUSE_MENU::INVALID OPTION VALUE\n");
					break;
				}
				break;
			default:
				break;

			}
		}

	}
}
