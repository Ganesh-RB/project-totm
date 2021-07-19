#include "stdafx.h"
#include "Level.h"

//private functions
void Level::initvariables()
{
	
	//CHAIN METHOD
	/*wall_generator.add_wall_chain(std::vector<sf::Vector2u>{ sf::Vector2u(2U, 19U), sf::Vector2u(10U, 19U), sf::Vector2u(10U, 18U), sf::Vector2u(11U, 18U), sf::Vector2u(11U, 17U), sf::Vector2u(12U, 17U), sf::Vector2u(12U, 8U),
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
	player.add_marker_chain(std::vector<sf::Vector2f>{sf::Vector2f(3.5f, 18.5f), sf::Vector2f(9.5f, 18.5f), sf::Vector2f(9.5f, 17.5f), sf::Vector2f(10.5f, 17.5f), sf::Vector2f(10.5f, 16.5f),
		sf::Vector2f(11.5f, 16.5f), sf::Vector2f(11.5f, 14.5f), sf::Vector2f(10.5f, 14.5f), sf::Vector2f(10.5f, 15.5f), sf::Vector2f(9.5f, 15.5f),
		sf::Vector2f(9.5f, 16.5f), sf::Vector2f(8.5f, 16.5f), sf::Vector2f(8.5f, 17.5f), sf::Vector2f(6.5f, 17.5f), sf::Vector2f(6.5f, 16.5f)});
	player.add_marker_chain(std::vector<sf::Vector2f>{ sf::Vector2f(3.5f, 18.5f), sf::Vector2f(3.5f, 16.5f), sf::Vector2f(5.5f, 16.5f), sf::Vector2f(5.5f, 15.5f), sf::Vector2f(9.5f, 15.5f),
		sf::Vector2f(9.5f, 9.5f), sf::Vector2f(11.5f, 9.5f), sf::Vector2f(11.5f, 10.5f), sf::Vector2f(10.5f, 10.5f), sf::Vector2f(10.5f, 13.5f) });
	player.add_marker_chain(std::vector<sf::Vector2f>{ sf::Vector2f(8.5f, 13.5f), sf::Vector2f(6.5f, 13.5f), sf::Vector2f(6.5, 12.5f), sf::Vector2f(7.5f, 12.5f), sf::Vector2f(7.5f, 11.5f),
		sf::Vector2f(8.5f, 11.5f), sf::Vector2f(8.5f, 9.5f), sf::Vector2f(5.5f, 9.5f), sf::Vector2f(5.5f, 11.5f), sf::Vector2f(3.5f, 11.5f), sf::Vector2f(3.5f, 10.5f),
		sf::Vector2f(6.5f, 10.5f) });*/

	this->assign(*m_context->m_level_no.get());

	this->alive = true;
	this->is_running = true;
	this->victory = false;
	this->time_mult = 60.f;
#if defined(_DEBUG)
	this->player.display_markers = true;
#endif
}


void Level::initfonts()
{
	gui_font = m_context->m_assets->get_font(asset_holder::fonts::DOSIS_LIGHT);
	endgame_font = m_context->m_assets->get_font(asset_holder::fonts::DOSIS_BOLD);
}
void Level::inittext()
{
	this->GUItext.setFont(this->gui_font);
	this->GUItext.setCharacterSize(24);
	this->GUItext.setFillColor(sf::Color::White);
	this->GUItext.setString(std::string("LEVEL ")+ std::to_string(*m_context->m_level_no.get()));
	this->end_game_text.setFont(this->endgame_font);
	this->end_game_text.setCharacterSize(60);
	this->end_game_text.setOutlineColor(sf::Color::Red);
	this->end_game_text.setFillColor(sf::Color(255, 255, 0, 255));
	this->end_game_text.setOutlineThickness(5.f);
	this->end_game_text.setString("GAME OVER!");
	this->end_game_text.setPosition(sf::Vector2f(60.f, 80.f));

}
void Level::defeat()
{
	this->alive = false;
	m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::DEATH);
	endlevel_timer.restart();
	end_game_text.setString("GAME OVER!");
}
void Level::win()
{
	m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::VICTORY);
	endlevel_timer.restart();
	end_game_text.setString("YOU WON !!");
	end_game_text.setFillColor(sf::Color::Blue);
	end_game_text.setOutlineColor(sf::Color::Green);
}
//constructors and destructors

Level::Level(std::shared_ptr<context>& context):m_context(context)
{
	is_pause = false;
	if (!Data::read(this->data))
		std::cout << "data file not readed correctly\n";
	//m_context->m_window->setFramerateLimit(60);
}

Level::~Level()
{
	m_context->m_window->setFramerateLimit(0);
}

//accessors
const bool Level::running() const
{
	return (this->is_running && this->m_context->m_window->isOpen());
}

const bool Level::assign(int lev_no)
{
    bool is_assign=false;
    for (auto _data = data.begin(); _data != data.end(); _data++)
    {
        if(_data->level_no==lev_no)
        {
            is_assign=true;
            this->player.setPosition(_data->Playerposition);

            for (auto coord = _data->wall_cordinates_sing.begin(); coord != _data->wall_cordinates_sing.end(); coord++)
            {
                this->wall_generator.add_wall_single(coord->first,coord->second.first,coord->second.second);
            }

            for (size_t i = 0; i < _data->wall_cordinates_mult.size(); i++)
            {
                this->wall_generator.add_wall_chain(_data->wall_cordinates_mult.at(i));
            }
            
            for (auto coord = _data->marker_pos_sing.begin(); coord != _data->marker_pos_sing.end(); _data++)
            {
                this->player.add_marker_single(*coord);
            }

            for (size_t i = 0; i < _data->marker_pos_mult.size(); i++)
            {
                this->player.add_marker_chain(_data->marker_pos_mult.at(i));
            }
        
            for (auto obs = _data->gun_arg.begin(); obs != _data->gun_arg.end(); obs++)
			{
				this->obstacles.push_back(new gun(obs->first,obs->second));
			}
		
            for (auto obs = _data->dragon_arg.begin(); obs != _data->dragon_arg.end(); obs++)
			{
				this->obstacles.push_back(new Dragon(obs->first,obs->second));
			}

            for (auto obs = _data->Pfish_arg.begin(); obs != _data->Pfish_arg.end(); obs++)
			{
				this->obstacles.push_back(new pufferfish(*obs));//
			}

            for (auto obs = _data->teleportal_arg.begin(); obs != _data->teleportal_arg.end(); obs++)
			{
				this->obstacles.push_back(new teleporter(obs->first,obs->second,player,m_context->m_assets.get() ));
			}		
		
			for (auto obs = _data->spring_arg.begin(); obs != _data->spring_arg.end(); obs++)
			{
				this->obstacles.push_back(new spring(obs->first,obs->second,player,m_context->m_assets.get() ));
			}
		}
    }

    return is_assign;    
}



//Overloaded state functions

void Level::init()
{
	this->initvariables();
	this->initfonts();
	this->inittext();
}

void Level::pollevents()
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
				m_context->m_assets->play_sound(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_sounds::BUTTON_BACKWARD);
				this->m_context->m_states->Add(std::make_unique<pause_menu>(m_context));
			}
			break;
		}
	}
}


void Level::update(float& _dt)
{
	dt = _dt;
	if (((!is_pause) && alive) && (!player.level_complete())) {

		this->player.update(m_context->m_window.get(), &dt, &time_mult);
		for (auto i : wall_generator.walls) {
			player.update_collision(&i);
		}

		for (auto obs : obstacles)
		{
			obs->update(this->dt);
		}
		
		for (auto obs : obstacles)
		{
			if (obs->isCollide(player.shape.getGlobalBounds())) {
				this->defeat();
				break;
			}
		}
		
		victory = player.level_complete();
		if (victory && alive) { 
			this->win();
		}
	}
	if (!alive && endlevel_timer.getElapsedTime().asSeconds() > 2.f) {
		m_context->m_states->Add(std::make_unique<death_menu>(m_context), true);
	}
	else if ((alive && victory) && endlevel_timer.getElapsedTime().asSeconds() > 2.f) {
		m_context->m_states->Add(std::make_unique<victory_menu>(m_context), true);
	}
}

void Level::render()
{
	this->m_context->m_window->clear();
	//draw game objects
	if (alive) {
		this->player.render(this->m_context->m_window.get());
	}
	this->wall_generator.render(this->m_context->m_window.get());

	
	for (auto obs : obstacles)
	{
		obs->render(this->m_context->m_window.get());
	}
	/*this->test_drag.render(this->m_context->m_window.get());*/
	if (victory || !alive) {
		this->m_context->m_window->draw(this->end_game_text);
	}
	this->m_context->m_window->draw(this->GUItext);
	this->m_context->m_window->display();
}

void Level::pause()
{
	is_pause = true;
}

void Level::start()
{
	pause_timer.restart();
	is_pause = false;
}
