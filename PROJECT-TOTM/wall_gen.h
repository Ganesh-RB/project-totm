
#ifndef WALL_GEN_H
#define WALL_GEN_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

////////////////////////////////////////////////////////////
	/// \brief enum for direction in which wall is to be made
	///
	////////////////////////////////////////////////////////////
enum wall_dir_no { LEFT, RIGHT, DOWN, UP };



////////////////////////////////////////////////////////////
/// \brief Class used to add walls quickly 
///
/// allows for walls to be added via chain or one by one
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

	////////////////////////////////////////////////////////////
	/// \brief sores if point is first point in chain or not
	///
	////////////////////////////////////////////////////////////
	bool chain_start;

	////////////////////////////////////////////////////////////
	/// \brief used as storage for the other point alogn with
	/// active one using which wall made in chain method
	///
	////////////////////////////////////////////////////////////
	sf::Vector2u chain_point;


public:
	//constructors and deconstructors
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// \param _color     color of the walls
	/// \param _base_size base size of player which is used to scale wall size
	///
	////////////////////////////////////////////////////////////
	wall_gen(sf::Color _color = sf::Color::Blue, float _base_size = 30.f);

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
	void add_wall_single(float x_coord, float y_coord, float len, wall_dir_no dir);

	////////////////////////////////////////////////////////////
	/*! \overload void add_wall_chain()
	*    overloaded null argument function to terminate variadic function
	*/
	////////////////////////////////////////////////////////////
	void add_wall_chain();

	////////////////////////////////////////////////////////////
	/// \brief used to add wall in chain fashion
	///
	/// enter any number of sf::Vector2u points in player units
	/// and this function will create vertical/horizontal walls
	/// with width equal player length between consecutive entered points
	///
	/// \param var1 first point
	/// \param ...var2 variadic argument for rest of entries
	///
	/// \note when constructing walls going downward/rightward
	/// direction ,their length extended by one to avoid cases of incomplete corner walls
	/// when the next wall segment is made
	/// 
	/// \warning consecutive points must be on same vertical/
	/// horizontal line ,or undefined behaviour
	///
	/// \warning if 2 consecutive points are the same then a player
	///sized block will be generated at that position
	/// 
	/// \warning no output/change if only one input given
	///
	////////////////////////////////////////////////////////////
	template <typename... ARGS>
	void add_wall_chain(sf::Vector2u var1, ARGS... var2)
	{
		if (chain_start == false) {
			sf::RectangleShape temp;
			temp.setFillColor(wall_colour);
			temp.setPosition(chain_point.x*base_size, chain_point.y*base_size);
			int temp_x = ((var1.x - chain_point.x) == 0) ? 1 : var1.x - chain_point.x;
			if (var1.x > chain_point.x) { temp_x += 1; }
			int temp_y = ((var1.y - chain_point.y) == 0) ? 1 : var1.y - chain_point.y;
			if (var1.y > chain_point.y) { temp_y += 1; }
			temp.setSize(sf::Vector2f(base_size*temp_x, base_size*temp_y));
			walls.push_back(temp);
		}
		else {
			chain_start = false;
		}
		chain_point = var1;
		wall_gen::add_wall_chain(var2...);
	}

	////////////////////////////////////////////////////////////
	/// \brief draws all members of walls on given target
	///
	/// \param target Target to draw to
	/// 
	////////////////////////////////////////////////////////////
	void render(sf::RenderTarget* target);
};
#endif