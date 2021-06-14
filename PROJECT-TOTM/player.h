#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#define BASE_SIZE  30.f

////////////////////////////////////////////////////////////
/// \brief class dealing with player movement,collision and markers
///
/// this class handles player movement ,collision and placement
/// of collectable markers which serve as victory condition
///
////////////////////////////////////////////////////////////
class player
{
private:

	////////////////////////////////////////////////////////////
	/// \brief used to initialize variables
	///
	/// sets movementspeed to required value and
	/// sets movement variables moving and move direction to initial values
	///
	////////////////////////////////////////////////////////////
	void initvariables();

	////////////////////////////////////////////////////////////
	/// \brief used to initialize player shape
	///
	/// initializes size and color of player shape
	////////////////////////////////////////////////////////////
	const void initshape();

	////////////////////////////////////////////////////////////
	/// \brief denotes player movement speed
	///
	////////////////////////////////////////////////////////////
	float movementspeed;

	////////////////////////////////////////////////////////////
	/// \brief used to indicate if grid has been colored
	///
	/// true when grid colored entirely,false otherwise
	///
	////////////////////////////////////////////////////////////
	bool all_grids_colored;


	////////////////////////////////////////////////////////////
	/// \brief used to indicate if point is at start of chain
	///
	/// true for first point given to add_marker_chain(),
	/// false otherwise
	///
	////////////////////////////////////////////////////////////
	bool marker_start;

	////////////////////////////////////////////////////////////
	/// \brief used to make sure grid entirely covered
	///
	/// used in updatemarkers() to ensure last bit of movement 
	////////////////////////////////////////////////////////////
	bool end_flag;

	//variables needed for time independent implementation

	////////////////////////////////////////////////////////////
	/// \brief denotes delta time
	///
	////////////////////////////////////////////////////////////
	float dt;

	////////////////////////////////////////////////////////////
	/// \brief denotes frame rate to be acheived
	///
	////////////////////////////////////////////////////////////
	float time_mult;

	//needed to draw trail lines

	//vector where all previously made trails are stored
	////////////////////////////////////////////////////////////
	/// \brief storage for all previously drawn trails
	///
	////////////////////////////////////////////////////////////
	std::vector<sf::RectangleShape> trails;

	////////////////////////////////////////////////////////////
	/// \brief denotes start of the trail being drawn
	///
	////////////////////////////////////////////////////////////
	sf::Vector2f start_trail;

	////////////////////////////////////////////////////////////
	/// \brief denotes end of trail at that moment
	///
	////////////////////////////////////////////////////////////
	sf::Vector2f end_trail;

	//shape which is for trail being drawn(if any)
	////////////////////////////////////////////////////////////
	/// \brief returns a trail given 2 points
	/// 
	////////////////////////////////////////////////////////////
	sf::RectangleShape curr_trail(sf::Vector2f* start, sf::Vector2f* end);

	//sets trail end depending on movemenet direction
	////////////////////////////////////////////////////////////
	/// \brief setsend_trail to where end of trail given movement direction
	///
	///  this function should only be called when movement happening 
	///  will not chnage end_trail variable otherwise
	/// 
	////////////////////////////////////////////////////////////
	void getendtrail(int);

	//vector where all markers are stored
	////////////////////////////////////////////////////////////
	/// \brief storage for all markers
	///
	////////////////////////////////////////////////////////////
	std::vector<sf::RectangleShape> markers;

	////////////////////////////////////////////////////////////
	/// \brief temporary marker object
	///
	/// used to set size,color,origin of all markers
	////////////////////////////////////////////////////////////
	sf::RectangleShape marker_temp;

	////////////////////////////////////////////////////////////
	/// \brief used for marker addition by chain
	///
	/// Used as storage for the other point along with
	/// active one between which markers added in
	/// add_marker_chain() function
	///
	////////////////////////////////////////////////////////////
	sf::Vector2f chain_point;

	////////////////////////////////////////////////////////////
	/// \brief used to ensure proper level completion
	///
    /// Used to make sure player moves certain distance after 
	/// collecting all markers before stopping so that entire 
	/// grid is colored 
	///
	////////////////////////////////////////////////////////////
	std::pair<sf::Vector2f, sf::Vector2f> ending_movement;


public:

	////////////////////////////////////////////////////////////
	/// \brief bool to display markers
	///
	/// if set to true ,markers are displayed otherwise 
	/// not displayed
	///
	////////////////////////////////////////////////////////////
	bool display_markers;

	////////////////////////////////////////////////////////////
	/// \brief used to check if level completed
	///
	/// if returns true means that all markers were collected
	/// and level has finished(grid has been colored entirely),
	/// false means still some squares uncolored
	///
	////////////////////////////////////////////////////////////
	bool level_complete();

	////////////////////////////////////////////////////////////
	/// \brief used to add markers in chain fashion
	///
	/// enter any number of sf::Vector2f points in player units
	/// and this function will create markers with spacing in the 
	/// x and/or y direction  equal to player length between 
	/// consecutive entered points
	///
	/// \param var1 first point
	/// \param ...var2 variadic argument for rest of entries
	///
	/// \note place markers in middle of grid squares
	/// 
	/// \warning no output/change if only one input given
	///
	/// \warning if 2 consecutive points are the same 
	/// then a single marker  will be generated at that position
	///
	////////////////////////////////////////////////////////////
	template <typename... ARGS>
	void add_marker_chain(sf::Vector2f var1, ARGS ...var2)
	{
		if (marker_start == false) {
			float max_y, max_x, min_y, min_x;
			if (var1.x > chain_point.x) {
				max_x = var1.x;
				min_x = chain_point.x;
			}
			else {
				max_x = chain_point.x;
				min_x = var1.x;
			}
			if (var1.y > chain_point.y) {
				max_y = var1.y;
				min_y = chain_point.y;
			}
			else {
				max_y = chain_point.y;
				min_y = var1.y;
			}

			while ((max_x - min_x >= 0.9f) || (max_y - min_y >= 0.9f)) {
				marker_temp.setPosition(sf::Vector2f(min_x*BASE_SIZE, min_y*BASE_SIZE));
				markers.push_back(marker_temp);
				min_x += (max_x - min_x >= 0.9f);
				min_y += (max_y - min_y >= 0.9f);
			}
			marker_temp.setPosition(sf::Vector2f(max_x*BASE_SIZE, max_y*BASE_SIZE));
			markers.push_back(marker_temp);
		}
		else {
			marker_start = false;
		}
		chain_point = var1;
		player::add_marker_chain(var2...);
	}

	////////////////////////////////////////////////////////////
	/*! \overload void add_marker_chain()
	*    overloaded null argument function to terminate variadic function
	*/
	////////////////////////////////////////////////////////////
	void add_marker_chain();

	////////////////////////////////////////////////////////////
	/// \brief used to add a single marker
	///
	/// enter coordinates of marker in player length units 
	/// to generate a marker at that position 
	///
	/// \param x x coordinate in player units
	/// \param y y coordinate in player units
	///
	/// \note place markers in middle of grid squares
	/// 
	////////////////////////////////////////////////////////////
	void add_marker_single(float x, float y);

	//cons and decons
	////////////////////////////////////////////////////////////
	/// \brief constructor
	///
	/// \param _x initial  x coordinate of player
	/// \param _y initial  y coordinate of player
	///
	////////////////////////////////////////////////////////////
	player(float _x = 0.f, float _y = 0.f);

	////////////////////////////////////////////////////////////
	/// \brief destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~player();

	//movement variables
	////////////////////////////////////////////////////////////
	/// \brief denotes if player moving or not
	///  
	/// false denotes player is stationary and 
	/// true denotes player is moving
	///
	////////////////////////////////////////////////////////////
	bool moving;

	////////////////////////////////////////////////////////////
	/// \brief denotes movement direction
	///
	/// 0 denotes no movement,1 for left,2 for right
	/// 3 for up and 4 for down
	///
	////////////////////////////////////////////////////////////
	int movedirection;

	////////////////////////////////////////////////////////////
	/// \brief used for square shaped player
	///
	////////////////////////////////////////////////////////////
	sf::RectangleShape shape;

	//returns coord of player object
	////////////////////////////////////////////////////////////
	/// \brief gives player coordinates
	///
	/// \return sf::vector2f showing x and y coordinates of player
	///
	////////////////////////////////////////////////////////////
	sf::Vector2f getcoord();

	//updates input and movement
	////////////////////////////////////////////////////////////
	/// \brief checks input,sets movement,changes start_trail accordingly
	///
	/// this function checks the input to see if movement
	/// key pressed ,changes movement accordingly and
	/// assigns a valid value to start-trail for given movement
	///
	////////////////////////////////////////////////////////////
	void updateinput();

	//checks for window collison 
	////////////////////////////////////////////////////////////
	/// \brief ensures player remains within screen 
	///
	///  checks if player is touching/out of screen and
	/// adjusts it's position and stops movement accordingly 
	///
	/// \param target pointer to window with which bounds is to be checked
	///
	////////////////////////////////////////////////////////////
	void updatewindowcollision(sf::RenderTarget* target);

	////////////////////////////////////////////////////////////
	/// \brief checks for collision with given object 
	///
	///  checks if player is colliding with object and
	/// adjusts it's position and stops movement accordingly
	///
	/// \param object pointer to object with which collision is to be checked
	///
	////////////////////////////////////////////////////////////
	void update_collision(sf::RectangleShape* object);

	////////////////////////////////////////////////////////////
	/// \brief checks for collision with given object 
	///
	///  checks if player is colliding with object and
	/// adjusts it's position and stops movement accordingly
	///
	/// \param object pointer to object with which collision is to be checked
	///
	////////////////////////////////////////////////////////////
	void updatemarkers();

	//generic update and vender
	////////////////////////////////////////////////////////////
	/// \brief generic update function
	///
	/// serves as container for all other update function/calls
	///
	/// \param target pointer to window in which object present
	/// \param _dt delta time value for which frame rate is adjusted
	/// \param _time_mult targeted value of fps
	/// for which frame rate independence is implemented
	///
	////////////////////////////////////////////////////////////
	void update(sf::RenderWindow* target, float* _dt, float* _time_mult);

	////////////////////////////////////////////////////////////
	/// \brief generic render function
	///
	/// serves as container for all other render functions/calls.
	///
	/// \param target pointer to window in 
	/// which object is to be rendered
	///
	////////////////////////////////////////////////////////////
	void render(sf::RenderWindow* target);

};

