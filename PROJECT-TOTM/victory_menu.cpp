#include "stdafx.h"
#include "victory_menu.h"

victory_menu::victory_menu(std::shared_ptr<context>& context) :gen_menu(context)
{
}

victory_menu::~victory_menu()
{
}

void victory_menu::variable_init()
{
	number_of_options = 4;
	for (int i = 0; i < number_of_options; i++) {
		options.emplace_back(sf::Text());
	}
	menu_title.setFillColor(sf::Color::Blue);
	color_text[0] = sf::Color::White;
	color_text[1] = sf::Color::Red;
	if (*m_context->m_level_no.get() == NUMBER_OF_LEVELS) {
		menu_title.setString("FINAL LEVEL CLEARED");
		options[1].setString("Select a level");
	}
	else {
		menu_title.setString("LEVEL CLEARED");
		options[1].setString("Next level");
	}
	options[0].setString("Main menu");
	options[2].setString("Retry Level");
	options[3].setString("Exit");

	title_font = &m_context->m_assets->get_font(asset_holder::fonts::DOSIS_EXTRABOLD);
	option_font = &m_context->m_assets->get_font(asset_holder::fonts::DOSIS_BOLD);
}

void victory_menu::pollevents()
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
					m_context->m_states->Add(std::make_unique<main_menu>(m_context), true);
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_BACKWARD);
					break;
				case 1:
					if (*m_context->m_level_no.get() == NUMBER_OF_LEVELS) {
						m_context->m_states->Add(std::make_unique<level_selector>(m_context), true);
						m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD);
					}
					else {
						(*m_context->m_level_no.get()) += 1;
						m_context->m_states->Add(std::make_unique<Level>(m_context), true);
						m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD);
					}
					break;
				case 2:
					m_context->m_states->Add(std::make_unique<Level>(m_context), true);
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD);
					break;
				case 3:
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

void victory_menu::update_anim(float dt)
{
	anim_timer += anim_dir * dt * 60;
	if (anim_timer > 60.f) { anim_dir = -1; }
	if (anim_timer < 0.f) { anim_dir = 1; }
	menu_title.setFillColor(sf::Color(0, (int)(anim_timer * 4)+10.f, 250-(int)(anim_timer*4), 255));
}

