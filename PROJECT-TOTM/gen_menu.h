#ifndef GEN_MENU_H
#define GEN_MENU_H

#include "context.h"

class gen_menu :public state
{
protected:
	std::shared_ptr<context>& m_context;
	sf::Text menu_title;
	sf::Color color_text[2];
	std::vector<sf::Text> options;
	int option_no[2];
	unsigned number_of_options=0;
public:
	gen_menu(std::shared_ptr<context>& context);
	virtual ~gen_menu();
	virtual void variable_init();
	virtual void init() override;
	virtual void pollevents() override =0;
	virtual void update(float& deltatime) override;
	virtual void render() override;
	

};
#endif
