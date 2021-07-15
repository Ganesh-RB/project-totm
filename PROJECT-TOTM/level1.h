#ifndef LEVEL1_H
#define LEVEL1_H

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

class level1 : public state
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
	sf::Clock death_timer;
	player player1{ 3.f,18.f,m_context->m_assets.get()};
	gun Gun1{ sf::Vector2u(11U,12U),sf::Vector2u(9U,12U)};
	pufferfish Fish1{ sf::Vector2u(7U,16U) };
	spring test_spring{ sf::Vector2f(3.f,10.f),spring::spring_dir::DOWN_RIGHT,player1,m_context->m_assets.get()};
	spring test_spring1{ sf::Vector2f(5.f,11.f),spring::spring_dir::UP_LEFT,player1,m_context->m_assets.get() };
	spring test_spring2{ sf::Vector2f(3.f,11.f),spring::spring_dir::UP_RIGHT,player1,m_context->m_assets.get()};
	teleporter test_tele{ sf::Vector2f(9.f,18.f), sf::Vector2f(5.f, 9.f),player1,m_context->m_assets.get() };
	/*Dragon test_drag{ sf::Vector2u(0U,0U),sf::Vector2u(3U,0U) }; */

	// initializers
	void initvariables();
	void initfonts();
	void inittext();
	void defeat();

	//fonts
	sf::Font font1;
	//text
	sf::Text GUItext;
	sf::Text deathtext;
public:
	//constructor and destructor
	level1(std::shared_ptr<context> &context);
	virtual ~level1();
	const bool running() const;
	wall_gen wall_generator{ 30.f };
	//functions from state 
	void init() override;
	void pollevents() override;
	void update(float& _dt) override;
	void render() override;
	void pause() override;
	void start() override;
};

#endif