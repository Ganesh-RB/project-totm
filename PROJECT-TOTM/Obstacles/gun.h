#ifndef GUN_H
#define GUN_H

#include "Obstacle.h"

class gun : public Obstacle
{
private:
	float BASE_SIZE = 30.f;
	sf::Vector2f GunPosition;
	sf::Vector2f TargetPosition;

	sf::Clock clock1_gun;
	sf::Sprite gunShape;
	sf::Texture guntexture;
	sf::IntRect gunCurrentFrame;
	sf::RectangleShape gunbackground;

	sf::Clock clock2_bullet;
	sf::Sprite bulletShape;
	sf::Texture bullettexture;
	sf::IntRect bulletCurrentFrame;


	///////////////////////////////////////////////////
	///
	/// \brief direction gives different types of directoin - Left , Down , Up , Right
	///
	///////////////////////////////////////////////////
	enum class direction { Left, Down, Up, Right }dir;
	
	double counter;
	int crabOpen;
	bool isMove;

	void initBullet();
	void initGunShape();
	void initSprite();
	void initDirection();

	void Animation(float dt);

public:

	///////////////////////////////////////////////////
	///	\brief constructor for initial setting of bullet
	///	
	/// \param GunPosition	sf::Vector2u position of gun in player coordinate
	/// \param TargetPosition sf::Vector2u position of target or last wall in player coordinate
	/// \param Type type of gun 
	///////////////////////////////////////////////////
	gun(sf::Vector2u GunPosition, sf::Vector2u TargetPosition);

	/////////////////////////////////////////////////////
	/////	\brief default destructor
	/////
	/////////////////////////////////////////////////////
	virtual ~gun();

	///////////////////////////////////////////////////
	///	\brief sets a gun position
	///	
	///	\param GunPosition
	///
	/// \see getGunPosition
	///
	///////////////////////////////////////////////////
	void setGunPosition(sf::Vector2f GunPosition);

	///////////////////////////////////////////////////
	///	\brief sets a target or wall position
	///	
	///	\param TargetPosition 
	///
	///////////////////////////////////////////////////
	void setTargetPosition(sf::Vector2f TargetPosition);

	///////////////////////////////////////////////////
	///	\brief  function fires a gun
	///	
	/// \param dt time for frame change(as s)-for frame rate independent	
	///
	///////////////////////////////////////////////////
	void update(const float dt);

	///////////////////////////////////////////////////
	///	\brief Draw everything for given gun
	///
	///////////////////////////////////////////////////
	void render(sf::RenderTarget* window);

	///////////////////////////////////////////////////
	///	
	///	\brief gives position of gun
	///	
	///	\return Gunposition sf::Vector2f
	///	
	///	\see setGunPosition
	///	
	///////////////////////////////////////////////////
	const sf::Vector2f getGunPosition();

	///////////////////////////////////////////////////
	///	
	///	\brief gives position of Target
	///	
	///	\return TargetPosition sf::Vector2f
	///	
	///	\see setTargetPosition
	///	
	///////////////////////////////////////////////////
	const sf::Vector2f getTargetPosition();

	///////////////////////////////////////////////////
	///	
	///	\brief check collision between bullets and shape
	///	
	///	\param shape RectangleShape to which collision is to be checked
	///	
	///	\return true if collide else false
	///	
	///////////////////////////////////////////////////
	const bool isCollide(const sf::FloatRect &shape) ;

	///////////////////////////////////////////////////
	///	
	///	\brief read the details of gun from the file
	///	
	///	\param fin std::ifstream& file stream
	///	\param data Data& file stream \file Data.h
	///	\param size size_t& file no of inputs to be taken
	///	
	///	
	///////////////////////////////////////////////////
	static void read(std::ifstream &fin, Data &data, size_t &size);

};


////////////////////////////////////////////////////////////
/// 
/// \class gun
///
/// \brief gun a obstacle which fires bullets regularly 
///
/// This class create a gun at a specified position with texture and make it move
///
/// Usage Example:
///
/// \code
///
/// gun Gun1(sf::Vector2f(10U,10U),sf::Vector2f(15U,10U));
///	Gun1.setGunPosition(sf::Vector2f(10U,10U));
///	Gun1.update(0.016f);
///	Gun1.render(this->window);
/// if(Gun1.isCollide(player.shape.getglobalound()))
///		//end game
///
/// \endcode
////////////////////////////////////////////////////////////

#endif // !GUN_H