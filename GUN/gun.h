#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#define n 2

enum class gunType {MultiBullets,SpeedVariance};

using namespace sf;
class gun
{
private:
	Vector2f GunPosition; /// position of gun 
	Vector2f TargetPosition; /// end position or position of wall
	RectangleShape Gunshape; /// shape of gun default value (30.f,30.f)
	RectangleShape Wallshape; /// shape of wall
	RectangleShape Bullets[n]; /// bullets 
	int i = 0; /// bullet index assuming 5 bullets are sufficient
	gunType Type;
	Vector2f dir; //direction

public:
	///////////////////////////////////////////////////
	///	\brief constructor 
	///	
	/// \param GunPosition	vector2f
	/// \param TargetPosition vector2f
	/// \param Type type of gun
	///////////////////////////////////////////////////
	gun(Vector2f gunposition,Vector2f targetposition,gunType _type);

	///////////////////////////////////////////////////
	///	\brief default constructor 
	///
	///////////////////////////////////////////////////
	gun();

	///////////////////////////////////////////////////
	///	\brief sets a gun position
	///	
	///	\param Gunposition 
	///
	///////////////////////////////////////////////////
	void setGunPosition(Vector2f gunposition);

	///////////////////////////////////////////////////
	///	\brief sets a target or wall position
	///	
	///	\param targetposition 
	///
	///////////////////////////////////////////////////
	void setTargetPosition(Vector2f targetposition);

	///////////////////////////////////////////////////
	///	\brief static function fires a gun for all gun
	///	
	///	\param any numbers of gun 
	///
	///////////////////////////////////////////////////
	void Gunfire();
	
	///////////////////////////////////////////////////
	///	\brief Draw everything for given gun
	///
	///////////////////////////////////////////////////
	void draw(RenderWindow& window);
};

#endif // !GUN_H
#pragma once
