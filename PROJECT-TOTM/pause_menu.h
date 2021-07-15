#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "gen_menu.h"

class pause_menu :public gen_menu
{
private:
	sf::Clock min_timer;
	
public:
	pause_menu(std::shared_ptr<context>& context);
	virtual ~pause_menu();
	void variable_init() override;
	void pollevents() override;

};
#endif