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
	/*gun Gun1{ sf::Vector2u(11U,12U),sf::Vector2u(9U,12U)};
	pufferfish Fish1{ sf::Vector2u(7U,16U) };
	spring test_spring{ sf::Vector2u(3U,10U),int(spring::spring_dir::DOWN_RIGHT),player1,m_context->m_assets.get()};
	spring test_spring1{ sf::Vector2u(5U,11U),int(spring::spring_dir::UP_LEFT),player1,m_context->m_assets.get() };
	spring test_spring2{ sf::Vector2u(3U,11U),int(spring::spring_dir::UP_RIGHT),player1,m_context->m_assets.get()};
	teleporter test_tele{ sf::Vector2u(9U,18U), sf::Vector2u(5U, 9U),player1,m_context->m_assets.get() };*/
	/*Dragon test_drag{ sf::Vector2u(0U,0U),sf::Vector2u(3U,0U) }; */

    std::vector<Obstacle*> obstacles;

    std::vector<Data> data;

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
	const bool running() const;
	wall_gen wall_generator{ 30.f };
	//functions from state 
    const bool assign(int lev_no);
	void init() override;
	void pollevents() override;
	void update(float& _dt) override;
	void render() override;
	void pause() override;
	void start() override;
};

#endif