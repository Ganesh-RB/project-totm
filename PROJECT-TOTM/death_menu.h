#ifndef DEATH_MENU_H
#define DEATH_MENU_H

#include "gen_menu.h"
#include "level1.h"
class death_menu : public gen_menu
{
public:
	death_menu(std::shared_ptr<context>& context);
	virtual ~death_menu();
	void variable_init() override;
	void pollevents() override;
};

#endif
