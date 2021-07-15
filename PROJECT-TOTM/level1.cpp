#include "stdafx.h"
#include "level1.h"

//private functions
void level1::initvariables()
{
	//CHAIN METHOD
	wall_generator.add_wall_chain(std::vector<sf::Vector2u>{ sf::Vector2u(2U, 19U), sf::Vector2u(10U, 19U), sf::Vector2u(10U, 18U), sf::Vector2u(11U, 18U), sf::Vector2u(11U, 17U), sf::Vector2u(12U, 17U), sf::Vector2u(12U, 8U),
		sf::Vector2u(4U, 8U), sf::Vector2u(4U, 9U), sf::Vector2u(2U, 9U), sf::Vector2u(2U, 12U), sf::Vector2u(5U, 12U), sf::Vector2u(5U, 14U), sf::Vector2u(4U, 14U), sf::Vector2u(4U, 15U), sf::Vector2u(2U, 15U),
		sf::Vector2u(2U, 19U) });
	//FLOATERS/SINGLE WALLS


	wall_generator.add_wall_single(sf::Vector2u(11U, 14U), 3, wall_generator.UP);
	wall_generator.add_wall_single(sf::Vector2u(4U, 17U), 2, wall_generator.RIGHT);
	wall_generator.add_wall_single(sf::Vector2u(7U, 16U), 1, wall_generator.RIGHT);
	wall_generator.add_wall_single(sf::Vector2u(6U, 11U), 1, wall_generator.RIGHT);
	wall_generator.add_wall_single(sf::Vector2u(7U, 10U), 1, wall_generator.RIGHT);
	wall_generator.add_wall_single(sf::Vector2u(8U, 12U), 1, wall_generator.RIGHT);
	wall_generator.add_wall_single(sf::Vector2u(6U, 14U), 3, wall_generator.RIGHT);
	player1.add_marker_chain(std::vector<sf::Vector2f>{sf::Vector2f(3.5f, 18.5f), sf::Vector2f(9.5f, 18.5f), sf::Vector2f(9.5f, 17.5f), sf::Vector2f(10.5f, 17.5f), sf::Vector2f(10.5f, 16.5f),
		sf::Vector2f(11.5f, 16.5f), sf::Vector2f(11.5f, 14.5f), sf::Vector2f(10.5f, 14.5f), sf::Vector2f(10.5f, 15.5f), sf::Vector2f(9.5f, 15.5f),
		sf::Vector2f(9.5f, 16.5f), sf::Vector2f(8.5f, 16.5f), sf::Vector2f(8.5f, 17.5f), sf::Vector2f(6.5f, 17.5f), sf::Vector2f(6.5f, 16.5f)});
	player1.add_marker_chain(std::vector<sf::Vector2f>{ sf::Vector2f(3.5f, 18.5f), sf::Vector2f(3.5f, 16.5f), sf::Vector2f(5.5f, 16.5f), sf::Vector2f(5.5f, 15.5f), sf::Vector2f(9.5f, 15.5f),
		sf::Vector2f(9.5f, 9.5f), sf::Vector2f(11.5f, 9.5f), sf::Vector2f(11.5f, 10.5f), sf::Vector2f(10.5f, 10.5f), sf::Vector2f(10.5f, 13.5f) });
	player1.add_marker_chain(std::vector<sf::Vector2f>{ sf::Vector2f(8.5f, 13.5f), sf::Vector2f(6.5f, 13.5f), sf::Vector2f(6.5, 12.5f), sf::Vector2f(7.5f, 12.5f), sf::Vector2f(7.5f, 11.5f),
		sf::Vector2f(8.5f, 11.5f), sf::Vector2f(8.5f, 9.5f), sf::Vector2f(5.5f, 9.5f), sf::Vector2f(5.5f, 11.5f), sf::Vector2f(3.5f, 11.5f), sf::Vector2f(3.5f, 10.5f),
		sf::Vector2f(6.5f, 10.5f) });
	this->alive = true;
	this->is_running = true;
	this->victory = false;
	this->time_mult = 60.f;
#if defined(_DEBUG)
	this->player1.display_markers = true;
#endif
}


void level1::initfonts()
{
	font1 = m_context->m_assets->get_font(asset_holder::fonts::DOSIS_LIGHT);
}
void level1::inittext()
{
	this->GUItext.setFont(this->font1);
	this->GUItext.setCharacterSize(24);
	this->GUItext.setFillColor(sf::Color::White);
	this->GUItext.setString("NONE");
	this->deathscreen.setFont(this->font1);
	this->deathscreen.setCharacterSize(60);
	this->deathscreen.setOutlineColor(sf::Color::Red);
	this->deathscreen.setFillColor(sf::Color(255, 255, 0, 255));
	this->deathscreen.setOutlineThickness(5.f);
	this->deathscreen.setString("YOU ARE DEAD !");
	this->deathscreen.setPosition(sf::Vector2f(60.f, 100.f));
}
void level1::defeat()
{
	this->alive = false;
	m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::DEATH);
}
//constructors and destructors
level1::level1(std::shared_ptr<context> &context) :m_context(context)
{
	is_pause = false;
	//m_context->m_window->setFramerateLimit(60);
}

level1::~level1()
{
	m_context->m_window->setFramerateLimit(0);
}

//accessors
const bool level1::running() const
{
	return (this->is_running && this->m_context->m_window->isOpen());
}

//Overloaded state functions

void level1::init()
{
	this->initvariables();
	this->initfonts();
	this->inittext();
}

void level1::pollevents()
{
	//event checking
	while (this->m_context->m_window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			if (ev.type == sf::Event::Closed) {
				this->is_running = false;
				this->m_context->m_window->close();
			}
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->is_running = false;
				this->m_context->m_window->close();
			}
			if (this->ev.key.code == sf::Keyboard::P && pause_timer.getElapsedTime().asSeconds() > 0.2f) {
				this->is_pause = true;

			}
			if (this->ev.key.code == sf::Keyboard::R && (!alive || victory))
			{
				m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_FORWARD);
				m_context->m_states->Add(std::make_unique<level1>(m_context), true);

			}
			break;
		}
	}
}


void level1::update(float& _dt)
{
	dt = _dt;
	if (((!is_pause) && alive) && (!player1.level_complete())) {

		this->player1.update(m_context->m_window.get(), &dt, &time_mult);
		for (auto i : wall_generator.walls) {
			player1.update_collision(&i);
		}
		test_tele.update(dt);
		/*test_drag.update(dt);*/
		Gun1.gunfire(this->dt, 1.f);
		Fish1.Updatefish(dt, 0.1f);
		test_spring.update(dt);
		test_spring1.update(dt);
		test_spring2.update(dt);
		if (Gun1.isCollide(player1.shape.getGlobalBounds())) {
			this->defeat();
		}
		if (Fish1.isCollide(player1.shape.getGlobalBounds())) {
			this->defeat();
		}
		victory = player1.level_complete();
		if (victory) { m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::VICTORY); }
	}
	if (is_pause && alive) {
		this->m_context->m_states->Add(std::make_unique<pause_menu>(m_context));
	}
}

void level1::render()
{
	this->m_context->m_window->clear();
	//draw game objects
	if (alive) {
		this->player1.render(this->m_context->m_window.get());
	}
	this->wall_generator.render(this->m_context->m_window.get());
	this->Gun1.Render_gun(this->m_context->m_window.get());
	this->Fish1.Render_fish(this->m_context->m_window.get());
	this->test_spring.render(this->m_context->m_window.get());
	this->test_spring1.render(this->m_context->m_window.get());
	this->test_spring2.render(this->m_context->m_window.get());
	this->test_tele.render(this->m_context->m_window.get());
	/*this->test_drag.render(this->m_context->m_window.get());*/
	if (!alive) {
		this->m_context->m_window->draw(this->deathscreen);
		GUItext.setString("Press R to Retry Level");
		this->m_context->m_window->draw(this->GUItext);
	}
	if (player1.level_complete()) {
		GUItext.setString("Level Complete!! Press R to play again");
		this->m_context->m_window->draw(this->GUItext);
	}


	this->m_context->m_window->display();

}

void level1::pause()
{
	is_pause = true;
}

void level1::start()
{
	pause_timer.restart();
	is_pause = false;
}
