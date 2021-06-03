#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

#define PlayerSize sf::Vector2f(30.f, 30.f)


///////////////////////////////////////////////////
///
/// \brief guntype gives different types of gun - Simple , Probablistic
///
///////////////////////////////////////////////////
enum class gunType { Simple, Probablistic };


///////////////////////////////////////////////////
///
/// \brief direction gives different types of directoin - Left , Down , Up , Right
///
///////////////////////////////////////////////////
enum class direction { Left, Down, Up, Right };



class gun
{
private:
	sf::Vector2f GunPosition;
	sf::Vector2f TargetPosition;

	sf::RectangleShape Gunshape;
	sf::ConvexShape Bullet;
	std::vector<sf::ConvexShape> Bullets;

	gunType Type;
	direction dir;
	int counter;

	void initBullet();
	void initGunShape();
	void initDirection();

public:

	///////////////////////////////////////////////////
	///	\brief constructor for initial setting of bullet
	///	
	/// \param GunPosition	sf::Vector2u position of gun in player coordinate
	/// \param TargetPosition sf::Vector2u position of target or last wall in player coordinate
	/// \param Type type of gun 
	///////////////////////////////////////////////////
	gun(sf::Vector2u GunPosition, sf::Vector2u TargetPosition, gunType Type);

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
	void gunfire(const float dt);

	///////////////////////////////////////////////////
	///	\brief Draw everything for given gun
	///
	///////////////////////////////////////////////////
	void Render_gun(sf::RenderWindow* window);

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
	const bool isCollide(const sf::FloatRect &shape);
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
/// gun Gun1(sf::Vector2f(10U,10U),sf::Vector2f(15U,10U),gunType::Simple);
///	Gun1.setGunPosition(sf::Vector2f(10U,10U));
///	Gun1.gunfire(0.016f);
///	Gun1.Render_gun();
///
/// \endcode
////////////////////////////////////////////////////////////

#endif // !GUN_H