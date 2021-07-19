#ifndef VICTORY_MENU_H
#define VICTORY_MENU_H

#include "gen_menu.h"
#include "main_menu.h"
class victory_menu : public gen_menu
{
private:
	float anim_timer=0.f;
	int anim_dir =1;
public:
	victory_menu(std::shared_ptr<context>& context);
	virtual ~victory_menu();
	void variable_init() override;
	void pollevents() override;
	void update_anim(float dt) override;
};

#endif