#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "gen_menu.h"
#include "level_selector.h"
#include "help_screen.h"

class main_menu :public gen_menu
{
private:
	
public:
	main_menu(std::shared_ptr<context>& context);
	virtual ~main_menu();
	void variable_init() override;
	void pollevents() override;

};
#endif