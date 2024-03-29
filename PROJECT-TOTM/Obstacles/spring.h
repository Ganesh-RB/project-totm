#ifndef SPRING_H
#define SPRING_H

#include "../player.h"
#include "../asset_holder.h"
#include "Obstacle.h"

class spring : public Obstacle
{
public:
	////////////////////////////////////////////////////////////
	/// \brief enum class for spring direction/type
	/// 
	////////////////////////////////////////////////////////////
	enum class spring_dir{DOWN_RIGHT,DOWN_LEFT,UP_LEFT, UP_RIGHT};

	////////////////////////////////////////////////////////////
	/// \brief constructor
	///
	/// \param _position sf::Vector2u position of spring in units of player size
	/// \param _dir int direction for spring created
	/// \param _player_var player& reference to player object
	/// \param asset_source  asset_holder* pointer to asset class to be used
	///
	////////////////////////////////////////////////////////////
	spring(sf::Vector2u _position,int _dir,player& _player_var, asset_holder* asset_source);

	////////////////////////////////////////////////////////////
	/// \brief destructor
	///
	////////////////////////////////////////////////////////////
	~spring();

	////////////////////////////////////////////////////////////
	/// \brief generic update function
	///
	/// serves as container for all other update function/calls
	///
	/// \param _dt float delta time value for which frame rate is adjusted
	///
	////////////////////////////////////////////////////////////
	void update(float dt);

	////////////////////////////////////////////////////////////
	/// \brief generic render function
	///
	/// serves as container for all other render functions/calls.
	///
	/// \param target sf::RenderTarget* pointer to window in 
	/// which object is to be rendered
	///
	////////////////////////////////////////////////////////////
	void render(sf::RenderTarget* target);

	////////////////////////////////////////////////////////////
	/// \brief implementation of pure virtual function of parent class
	///
	/// \param sf::FloatRect& any floatrect
	/// 
	/// this function is a pure virtual from parent class which
	/// is given the simple implementation of always returning false
	/// as spring class can not kill the player
	/// 
	/// \return bool always returns false
	///
	////////////////////////////////////////////////////////////
	const bool isCollide(const sf::FloatRect &shape);

	///////////////////////////////////////////////////
	///	
	///	\brief read the details of spring from the file
	///	
	///	\param fin std::ifstream& file stream
	///	\param data Data& file stream \file Data.h
	///	\param size size_t& file no of inputs to be taken
	///	
	///	
	///////////////////////////////////////////////////
	static void read(std::ifstream &fin, Data &data, size_t &size);

private:
	////////////////////////////////////////////////////////////
	/// \brief size of spring
	///
	////////////////////////////////////////////////////////////
	float BASE_SIZE;

	////////////////////////////////////////////////////////////
	/// \brief times bounce animation timing
	///
	////////////////////////////////////////////////////////////	
	float timer_bounce;

	////////////////////////////////////////////////////////////
	/// \brief times general animation timing
	///
	////////////////////////////////////////////////////////////
	float timer;

	////////////////////////////////////////////////////////////
	/// \brief scales by how much timer chnages and in
	/// which direction
	///
	////////////////////////////////////////////////////////////
	float anim_flash;

	////////////////////////////////////////////////////////////
	/// \brief indicates whether spring is "active" or not
	///
	////////////////////////////////////////////////////////////
	bool is_active;

	////////////////////////////////////////////////////////////
	/// \brief indicates whether bounce animation is 
	/// playing or not
	///
	////////////////////////////////////////////////////////////
	bool bounce_animation;

	////////////////////////////////////////////////////////////
	/// \brief point used for changing player direction
	///
	////////////////////////////////////////////////////////////
	sf::Vector2f trigger_point;

	////////////////////////////////////////////////////////////
	/// \brief sprite showing spring texture
	///
	////////////////////////////////////////////////////////////
	sf::Sprite spring_sprite;

	////////////////////////////////////////////////////////////
	/// \brief sf::floatrect for sprite
	///
	////////////////////////////////////////////////////////////
	sf::IntRect currentframe;

	////////////////////////////////////////////////////////////
	/// \brief player reference to player object for which
	/// spring works 
	///
	////////////////////////////////////////////////////////////
	player& player_var;

	////////////////////////////////////////////////////////////
	/// \brief asset holder from which textures and files used
	///
	////////////////////////////////////////////////////////////
	asset_holder& m_assets;

	////////////////////////////////////////////////////////////
	/// \brief initializes variables
	///
	////////////////////////////////////////////////////////////
	void initvariables();

	////////////////////////////////////////////////////////////
	/// \brief deals with animations
	///
	////////////////////////////////////////////////////////////
	void animation(float _dt);

	////////////////////////////////////////////////////////////
	/// \brief direction of spring 
	///
	////////////////////////////////////////////////////////////
	spring_dir dir;

	////////////////////////////////////////////////////////////
	/// \brief player movement directions and their 
	/// transformations corresponding to spring direction 
	/// 
	////////////////////////////////////////////////////////////
	std::pair <player::move_dir_no[2],player::move_dir_no[2]> directions;

};

////////////////////////////////////////////////////////////
/// 
/// \class spring
///
/// \brief class for the spring obstacle
///
/// this class creates a spring object which manipulates movement
/// of player given in constructor by changing its direction upon
/// collision.this class is a friend class of player
///
////////////////////////////////////////////////////////////

#endif 