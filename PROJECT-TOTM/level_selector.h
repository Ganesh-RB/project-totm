#ifndef LEVEL_SELECTOR_H
#define LEVEL_SELECTOR_H

#include "context.h"
#include "Level.h"

#define NUMBER_OF_LEVELS 2U
class level_selector : public state
{
private:
	std::shared_ptr<context>& m_context;
	sf::Font* title_font;
	sf::Font* body_font;
	sf::Text title_text;
	sf::Text level_text;
	sf::Text level_count_text;
	unsigned level_number=1;
	sf::CircleShape uparrow;
	sf::CircleShape downarrow;
public:
	level_selector(std::shared_ptr<context>& context);
	~level_selector();
	void init() override;
	void pollevents() override;
	void update(float& dt) override;
	void render() override;


};

#endif