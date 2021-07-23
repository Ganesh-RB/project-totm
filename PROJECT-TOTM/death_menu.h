#ifndef DEATH_MENU_H
#define DEATH_MENU_H

#include "gen_menu.h"
#include "Level.h"
#include "main_menu.h"
class death_menu : public gen_menu
{
public:
	////////////////////////////////////////////////////////////
	/// \brief constructor
	///
	/// \param context std::shared_ptr<context>& shared 
	/// reference to the active context
	///
	////////////////////////////////////////////////////////////
	death_menu(std::shared_ptr<context>& context);

	////////////////////////////////////////////////////////////
	/// \brief destructor
	/// 
	////////////////////////////////////////////////////////////
	virtual ~death_menu();

	// overrides from gen_menu
	////////////////////////////////////////////////////////////
	/// \brief override of pure virtual gen_menu class function variable_init()
	/// this initializes variables which change from menu to menu
	/// 
	////////////////////////////////////////////////////////////
	void variable_init() override;

	////////////////////////////////////////////////////////////
	/// \brief override of pure virtual gen_menu class function pollevents()
	/// this initializes the input processing and actions
	/// 
	////////////////////////////////////////////////////////////
	void pollevents() override;
};

////////////////////////////////////////////////////////////
/// 
/// \class death_menu
///
/// \brief class for the death screen
///
/// This class creates a death menu with options of restarting
/// going to the main menu or exiting the game,this class is 
/// derived from gen_menu class
///
////////////////////////////////////////////////////////////

#endif
