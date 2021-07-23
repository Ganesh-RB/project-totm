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
	////////////////////////////////////////////////////////////
	/// \brief constructor
	///
	/// \param context std::shared_ptr<context>& shared 
	/// reference to the active context
	///
	////////////////////////////////////////////////////////////
	victory_menu(std::shared_ptr<context>& context);

	////////////////////////////////////////////////////////////
	/// \brief destructor
	/// 
	////////////////////////////////////////////////////////////
	virtual ~victory_menu();

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

	////////////////////////////////////////////////////////////
	/// \brief override of virtual gen_menu class function update_anim()
	/// this initializes the animation of menu
	/// 
	////////////////////////////////////////////////////////////
	void update_anim(float dt) override;
};

////////////////////////////////////////////////////////////
/// 
/// \class victory_menu
///
/// \brief class for the victory screen
///
/// This class creates a victory menu with options of ,
/// going to the next level,restarting level, to the main menu
/// or exiting the game,this class is derived from gen_menu
/// class
///
////////////////////////////////////////////////////////////

#endif