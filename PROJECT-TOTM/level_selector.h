#ifndef LEVEL_SELECTOR_H
#define LEVEL_SELECTOR_H

#include "context.h"
#include "Level.h"

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
	////////////////////////////////////////////////////////////
	/// \brief constructor
	///
	/// \param context std::shared_ptr<context>& shared 
	/// reference to the active context
	///
	////////////////////////////////////////////////////////////
	level_selector(std::shared_ptr<context>& context);

	////////////////////////////////////////////////////////////
	/// \brief destructor
	/// 
	////////////////////////////////////////////////////////////
	~level_selector();

	// overrides from state parent class

	////////////////////////////////////////////////////////////
	/// \brief override of pure virtual state class function init()
	/// this initializes the class
	/// 
	////////////////////////////////////////////////////////////
	void init() override;

	////////////////////////////////////////////////////////////
	/// \brief override of pure virtual state class function pollevents()
	/// this takes input for the class
	/// 
	////////////////////////////////////////////////////////////
	void pollevents() override;

	////////////////////////////////////////////////////////////
	/// \brief override of pure virtual state class function update(float& dt)
	/// this takes deltatime as float for the class
	/// 
	////////////////////////////////////////////////////////////
	void update(float& dt) override;

	////////////////////////////////////////////////////////////
	/// \brief override of pure virtual state class function render()
	/// this renders the class on context's window
	/// 
	////////////////////////////////////////////////////////////
	void render() override;

};

////////////////////////////////////////////////////////////
/// 
/// \class level_selector
///
/// \brief class for the level selection screen
///
/// This class creates a level selection menu with options of
/// choosing a level .
///
////////////////////////////////////////////////////////////

#endif