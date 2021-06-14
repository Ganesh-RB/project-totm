#pragma once
#include "player.h"
#include "wall_gen.h"
#include "Obstacles/gun.h"
#include "game.h"
class level1 : public state
{
private:
	//window

	sf::Event ev;
	//private functions
	std::shared_ptr<context> m_context;
	float dt;
	float time_mult;

	bool is_pause;
	bool alive;
	bool is_running;
	bool victory;
	sf::Clock pause_timer;
	player player1{ 3.f,18.f };
	gun Gun1{ sf::Vector2u(11U,12U),sf::Vector2u(9U,12U) };

	// initializers
	void initvariables();
	void initfonts();
	void inittext();

	//fonts
	sf::Font font1;
	//text
	sf::Text GUItext;
	sf::Text deathscreen;
public:
	//constructor and destructor
	level1(std::shared_ptr<context> &context);
	virtual ~level1();
	//sf::Sprite sprite1;
	//sf::Texture texture;
	const bool running() const;
	wall_gen wall_generator{30.f};
	//functions from state 
	void init() override;
	void pollevents() override;
	void update(float& _dt) override ;
	void render() override;
	void pause() override;
	void start() override;
};