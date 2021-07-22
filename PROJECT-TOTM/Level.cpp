#include "stdafx.h"
#include "Level.h"

//private functions
void Level::initvariables()
{
	
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
	this->player.set_player_dead();
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
				this->obstacles.push_back(new gun(obs->first, obs->second, m_context->m_assets.get()));
			}
		
            for (auto obs = _data->dragon_arg.begin(); obs != _data->dragon_arg.end(); obs++)
			{
				this->obstacles.push_back(new Dragon(obs->first, obs->second, m_context->m_assets.get()));
			}

            for (auto obs = _data->Pfish_arg.begin(); obs != _data->Pfish_arg.end(); obs++)
			{
				this->obstacles.push_back(new pufferfish(*obs, m_context->m_assets.get()));
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
	if (!alive) { player.update(m_context->m_window.get(), &dt, &time_mult); }
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

	this->player.render(this->m_context->m_window.get());
	this->wall_generator.render(this->m_context->m_window.get());

	
	for (auto obs : obstacles)
	{
		obs->render(this->m_context->m_window.get());
	}
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
