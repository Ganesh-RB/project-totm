#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "wall_gen.h"
#include "context.h"
#include "Obstacles/gun.h"
#include "Obstacles/pufferfish.h"
#include "Obstacles/teleporter.h"
#include "Obstacles/Dragon.h"
#include "Obstacles/spring.h"
#include "pause_menu.h"
#include "death_menu.h"
#include "victory_menu.h"
#include "define.h"

class Level : public state
{
private:
	//window
	sf::Event ev;
	//private functions
	std::shared_ptr<context>& m_context;
	float dt;
	float time_mult;
	bool is_pause;
	bool alive;
	bool is_running;
	bool victory;

	sf::Clock pause_timer;
	sf::Clock endlevel_timer;

	player player{m_context->m_assets.get()};
	

    std::vector<Obstacle*> obstacles;


	// initializers
	void initvariables();
	void initfonts();
	void inittext();
	//functions dealing with end game situations
	void defeat();
	void win();

	//fonts
	sf::Font gui_font;
	sf::Font endgame_font;
	//text
	sf::Text GUItext;
	sf::Text end_game_text;
public:
	//constructor and destructor
	Level(std::shared_ptr<context> &context);
	virtual ~Level();
	wall_gen wall_generator{ PLAYER_BASE_SIZE };
	//functions from state 
    const bool assign(int lev_no);
	void init() override;
	void pollevents() override;
	void update(float& _dt) override;
	void render() override;
	void pause() override;
	void start() override;
};

////////////////////////////////////////////////////////////
/// 
/// \class Level
///
/// \brief generalized level class
///
/// this class stores all level info and performs the running
/// of level by getting info such as level data,assets and 
/// statestack from the context in its constructor.
///
////////////////////////////////////////////////////////////
#endif