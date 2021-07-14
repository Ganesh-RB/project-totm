#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "context.h"

class pause_menu :public state
{
private:
	std::shared_ptr<context>& m_context;
	sf::Text menu_title;
	sf::Color color_text[2];
	sf::Text options[3];
	int option_no[2];
	sf::Clock min_timer;
	
public:
	pause_menu(std::shared_ptr<context>& context);
	virtual ~pause_menu();
	void init() override;
	void pollevents() override;
	void update(float& deltatime) override;
	void render() override;

};
#endif