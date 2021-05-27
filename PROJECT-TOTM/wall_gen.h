#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
////////////////////////////////////////////////////////////
/// \brief Class used to add walls quickly 
///
////////////////////////////////////////////////////////////
class wall_gen
{
private:
    ////////////////////////////////////////////////////////////
    /// \brief private variable used to store player size
	///
    ////////////////////////////////////////////////////////////
	float base_size = 30.f; 

	////////////////////////////////////////////////////////////
    /// \brief stores color of walls
    ///
    ////////////////////////////////////////////////////////////
	sf::Color wall_colour;  
	

public:
	//constructors and deconstructors
	////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param _color     color of the walls
    /// \param _base_size base size of player which is used to scale wall size
    ///
    ////////////////////////////////////////////////////////////
	wall_gen(sf::Color _color=sf::Color::Blue,float _base_size=30.f);

    ////////////////////////////////////////////////////////////
    /// \brief Virtual destructor
    ///
    ////////////////////////////////////////////////////////////
	virtual ~wall_gen();

	// public member data
    ////////////////////////////////////////////////////////////
    /// \brief vector containing all the individual walls
    ///
    ////////////////////////////////////////////////////////////
	std::vector<sf::RectangleShape> walls;

	////////////////////////////////////////////////////////////
	/// \brief enum for direction in which wall is to be made
	///
	////////////////////////////////////////////////////////////
	enum wall_dir_no { LEFT, RIGHT, DOWN, UP };

	//functions
	////////////////////////////////////////////////////////////
	/// \brief adds a wall to the storage vector 
	///
	///  wall is added to walls container using given coordinates ,length
	///  and direction in terms of player units,i.e if length(or breadth)
	///  of square player is 10 then the new wall's position will be set to (10*x_coord,10*y_coord)
	///  length will be len*10 and direction as given by dir
	///
	///  \param x_coord x coordinate in terms of player length
	///  \param y_coord y coordinate in terms of player length
	///  \param len length in terms of player length
	///  \param dir direction as given in wall_dir_no
	///  
	////////////////////////////////////////////////////////////
	void add_wall(float x_coord, float y_coord, float len, wall_dir_no dir);

	////////////////////////////////////////////////////////////
	/// \brief draws all members of walls on given target
	///
	/// \param target Target to draw to
	/// 
	////////////////////////////////////////////////////////////
	void render(sf::RenderTarget* target);
};
