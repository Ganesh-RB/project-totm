#ifndef WALL_GEN_H
#define WALL_GEN_H


////////////////////////////////////////////////////////////
/// \brief Class used to add walls quickly 
///
/// allows for walls to be added via chain or one by one
////////////////////////////////////////////////////////////
class wall_gen
{
private:
	////////////////////////////////////////////////////////////
	/// \brief variable where pixel pattern specified
	/// to be applied to wall
	///
	////////////////////////////////////////////////////////////
	sf::Image bitwise_image;

	////////////////////////////////////////////////////////////
	/// \brief variable used to apply texture to wall
	///
	////////////////////////////////////////////////////////////
	sf::Texture wall_tex;

	////////////////////////////////////////////////////////////
	/// \brief private variable used to store player size
	///
	////////////////////////////////////////////////////////////
	float base_size = 30.f;

public:
	//constructors and deconstructors
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// \param _base_size base size of player which is used to scale wall size
	///
	////////////////////////////////////////////////////////////
	wall_gen(float _base_size = 30.f);

	////////////////////////////////////////////////////////////
	/// \brief Virtual destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~wall_gen();

	// public member data
	
	////////////////////////////////////////////////////////////
	/// \brief enum for direction in which wall is to be made
	///
	////////////////////////////////////////////////////////////
	enum wall_dir_no { LEFT, RIGHT, DOWN, UP };
	
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
	void add_wall_single(const sf::Vector2u coord, int len, wall_dir_no dir);


	////////////////////////////////////////////////////////////
	/// \brief used to add wall in chain fashion
	///
	/// enter a vector of sf::Vector2u points in player units
	/// and this function will create vertical/horizontal walls
	/// with width equal player length between consecutive  
	/// points in vector
	///
	/// \param points vector of sf::vector2u points
	///
	/// \note when constructing walls going downward/rightward
	/// direction ,their length extended by one to avoid cases of incomplete corner walls
	/// when the next wall segment is made
	/// 
	/// \warning consecutive points must be on same vertical/
	/// horizontal line ,or undefined behaviour
	///
	/// \warning if 2 consecutive points are the same then a player
	/// sized block will be generated at that position
	/// 
	/// \warning no output/change if only zero or one point in vector
	///
	////////////////////////////////////////////////////////////
	void add_wall_chain(const std::vector<sf::Vector2u>& points);

	////////////////////////////////////////////////////////////
	/// \brief draws all members of walls on given target
	///
	/// \param target Target to draw to
	/// 
	////////////////////////////////////////////////////////////
	void render(sf::RenderTarget* target);
};
#endif
