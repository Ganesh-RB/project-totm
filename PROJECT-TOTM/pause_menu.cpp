#include "stdafx.h"
#include "pause_menu.h"

pause_menu::pause_menu(std::shared_ptr<context>& context):m_context(context)
{
}

pause_menu::~pause_menu()
{
}

void pause_menu::init()
{
	menu_title.setFont(m_context->m_assets->get_font(asset_holder::fonts::DOSIS_EXTRABOLD));
	menu_title.setCharacterSize(60);
	menu_title.setFillColor(sf::Color::Green);
	menu_title.setString("PAUSED");
	menu_title.setOrigin(menu_title.getLocalBounds().width / 2.f, 0);
	menu_title.setPosition(m_context->m_window->getSize().x / 2.f, 0.f);

	color_text[0] = sf::Color::White;
	color_text[1] = sf::Color::Red;
	options[0].setString("Resume");
	options[0].setPosition(m_context->m_window->getSize().x / 3.f, m_context->m_window->getSize().y / 2.f - 50.f);
	options[0].setFillColor(color_text[1]);
	options[1].setString("Main menu");
	options[1].setPosition(m_context->m_window->getSize().x / 3.f, m_context->m_window->getSize().y / 2.f);
	options[1].setFillColor(color_text[0]);
	options[2].setString("Exit");
	options[2].setPosition(m_context->m_window->getSize().x / 3.f, m_context->m_window->getSize().y / 2.f + 50.f);
	options[2].setFillColor(color_text[0]);
	option_no[0] = 0;
	option_no[1] = 0;
	for (auto& i : options) {
		i.setFont(m_context->m_assets->get_font(asset_holder::fonts::DOSIS_BOLD));
		i.setCharacterSize(30);
		i.setOrigin(i.getLocalBounds().width / 2.f, 0);

	}
}

void pause_menu::pollevents()
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
				if (option_no[0] < 2) {
					option_no[0] += 1;
					m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS,asset_holder::ojjas_sounds::BEEP);
				}
				break;
			case sf::Keyboard::Enter:
				switch (option_no[0]) {
				case 0:
					m_context->m_states->Popcurrent();
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

void pause_menu::update(float & deltatime)
{
	if (option_no[0] != option_no[1]) {
		for (auto& i : options) { i.setFillColor(color_text[0]); }
		options[option_no[0]].setFillColor(color_text[1]);
		option_no[1] = option_no[0];
	}
}

void pause_menu::render()
{
	m_context->m_window->clear();
	m_context->m_window->draw(menu_title);
	for (const auto i : options) {
		m_context->m_window->draw(i);
	}
	m_context->m_window->display();
}
