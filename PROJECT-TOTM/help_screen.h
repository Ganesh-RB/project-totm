#ifndef HELP_SCREEN_H
#define HELP_SCREEN_H

#include "context.h"
class help_screen : public state
{
private:
	std::shared_ptr<context>& m_context;
	sf::Text Helpfull_text;

public:
	help_screen(std::shared_ptr<context>& context);
	~help_screen();
	void init() override;
	void pollevents() override;
	void update(float& deltatime) override;
	void render() override;
};

#endif