#include "stdafx.h"
#include "gen_menu.h"

gen_menu::gen_menu(std::shared_ptr<context>& context) :m_context(context)
{
}

gen_menu::~gen_menu()
{
}
void gen_menu::variable_init()
{
	number_of_options = 3;
	for (int i = 0; i < number_of_options; i++) {
		options.emplace_back(sf::Text());
	}
	menu_title.setFillColor(sf::Color::Green);
	color_text[0] = sf::Color::White;
	color_text[1] = sf::Color::Red;
	title_font = &m_context->m_assets->get_font(asset_holder::fonts::DOSIS_EXTRABOLD);
	option_font = &m_context->m_assets->get_font(asset_holder::fonts::DOSIS_BOLD);
	menu_title.setString("GIVE ME A TITLE");
	options[0].setString("I am an option");
	options[1].setString("I am also an option");
	options[2].setString("Don't forget me either");
}
void gen_menu::init()
{
	variable_init();
	menu_title.setFont(*title_font);
	menu_title.setCharacterSize(60);
	option_no[0] = 0;
	option_no[1] = 0;
	menu_title.setOrigin(menu_title.getLocalBounds().width / 2.f, 0);
	menu_title.setPosition(m_context->m_window->getSize().x / 2.f, 0.f);
	for (int i = 0; i < number_of_options;i++) {
		options[i].setFont(*option_font);
		options[i].setCharacterSize(30);
		options[i].setPosition(m_context->m_window->getSize().x / 3.f, m_context->m_window->getSize().y / 2.f +(i-2)*50.f);
		options[i].setFillColor(color_text[0]);
	}
	options[0].setFillColor(color_text[1]);
}

void gen_menu::update(float & deltatime)
{
	if (option_no[0] != option_no[1]) {
		for (auto& i : options) { i.setFillColor(color_text[0]); }
		options[option_no[0]].setFillColor(color_text[1]);
		option_no[1] = option_no[0];
	}
}

void gen_menu::render()
{
	m_context->m_window->clear();
	m_context->m_window->draw(menu_title);
	for (const auto i : options) {
		m_context->m_window->draw(i);
	}
	m_context->m_window->display();
}
