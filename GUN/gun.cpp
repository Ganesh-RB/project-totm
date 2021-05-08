#include "gun.h"
#include <iostream>
#include <math.h>

gun::gun()
{
	GunPosition = Vector2f(0.f, 0.f);
	TargetPosition = Vector2f(0.f, 0.f);

	Gunshape.setSize(Vector2f(30.f, 30.f));
	Gunshape.setPosition(GunPosition);
	//Gunshape.setFillColor();
	Gunshape.setFillColor(Color::Magenta);

	Wallshape.setSize(Vector2f(30.f, 30.f));
	Wallshape.setPosition(TargetPosition);
	//Wallshape.setFillColor();
	Wallshape.setFillColor(Color::Magenta);

	//bullet initialisation
	for (int j = 0; j < n; j++)
	{
		Bullets[j].setSize(Vector2f(30.f, 30.f));
		Bullets[j].setFillColor(Color(255,255,60*j,255));
		Bullets[j].setPosition(GunPosition);

	}

	Bullets[0].setFillColor(Color(100, 100, 100, 0));
	Type = gunType::SpeedVariance;
}

gun::gun(Vector2f gunposition, Vector2f targetposition, gunType _type)
{
	GunPosition = gunposition;
	TargetPosition = targetposition;

	Gunshape.setSize(Vector2f(30.f, 30.f));
	Gunshape.setPosition(GunPosition);
	//Gunshape.setFillColor();
	Gunshape.setFillColor(Color::Magenta);

	Wallshape.setSize(Vector2f(30.f, 30.f));
	Wallshape.setPosition(TargetPosition);
	//Wallshape.setFillColor();
	Wallshape.setFillColor(Color::Magenta);

	//bullet initialiation
	for (int j = 0; j < n; j++)
	{
		Bullets[j].setSize(Vector2f(30.f, 30.f));
		Bullets[j].setFillColor(Color::Cyan);
		Bullets[j].setPosition(GunPosition);

	}
	Type = _type;
	
	dir.x = TargetPosition.x - GunPosition.x == 0.f ? 0.f : (TargetPosition.x - GunPosition.x) / fabsf(TargetPosition.x - GunPosition.x);
	dir.y = TargetPosition.y - GunPosition.y == 0.f ? 0.f : (TargetPosition.y - GunPosition.y) / fabsf(TargetPosition.y - GunPosition.y);
	std::cout << dir.x << " : " << dir.y << std::endl;

}

void gun::setGunPosition(Vector2f gunposition)
{
	GunPosition = gunposition;
	Gunshape.setPosition(GunPosition);
}

void gun::setTargetPosition(Vector2f targetposition)
{
	TargetPosition = targetposition;
	Wallshape.setPosition(TargetPosition);
}

void gun::Gunfire()
{

	if (Type == gunType::MultiBullets)
	{
		if (fabsf(TargetPosition.x - Bullets[i].getPosition().x) <= Wallshape.getSize().x && fabsf(TargetPosition.y - Bullets[i].getPosition().y) <= Wallshape.getSize().y)
		{
			Bullets[i].setPosition(GunPosition);
			i = (i + 1) % n;
			std::cout << "inside touching condition\n";
			/*std::cout << "block touches by gun :" << 0 << std::endl;*/
		}
		//if (TargetPosition.x == Bullets[i].getPosition().x + Wallshape.getSize().x)
		//{
		//	Bullets[i].setPosition(GunPosition);
		//	i = (i + 1) % n;
		//	//std::cout << "block touches by gun :" << i << std::endl;
		//}

		if (fabsf(Bullets[i].getPosition().x - GunPosition.x + Bullets[i].getPosition().y - GunPosition.y) > 300)
		{
			if (fabsf(Bullets[i].getPosition().x - GunPosition.x + Bullets[i].getPosition().y - GunPosition.y) > 600)
			{
				Bullets[i].move(dir);
				Bullets[((i + 1) % n)].move(dir);
				Bullets[((i + 2) % n)].move(dir);
			}
			else
			{
				Bullets[i].move(dir);
				Bullets[((i + 1) % n)].move(dir);
			}
		}
		else
		{

			Bullets[i].move(dir);
		}
	}
	if (Type == gunType::SpeedVariance)
	{
		//std::cout << fabsf(TargetPosition.x - Bullets[0].getPosition().x) << " : " << fabsf(TargetPosition.y - Bullets[0].getPosition().y) << std::endl;
		if (fabsf(TargetPosition.x - Bullets[0].getPosition().x) <= Wallshape.getSize().x && fabsf(TargetPosition.y - Bullets[0].getPosition().y) <= Wallshape.getSize().y)
		{
			Bullets[0].setPosition(GunPosition);
			std::cout << "inside touching condition\n";
			/*std::cout << "block touches by gun :" << 0 << std::endl;*/
		}


		float speed = fabsf(Wallshape.getPosition().x - GunPosition.x + Wallshape.getPosition().y - GunPosition.y)/200;
		Bullets[0].move(Vector2f(speed*(dir.x), speed*(dir.y)));
		std::cout<<"move by "<<speed*(dir.x)<<" : " <<speed*(dir.y)<<std::endl;
		
	}
//	std::cout << Bullets[i].getPosition().x - GunPosition.x << " ::: " << Bullets[0].getPosition().x << " : " << Bullets[1].getPosition().x << " : " << Bullets[2].getPosition().x << " : " << Bullets[3].getPosition().x << " : " << Bullets[4].getPosition().x << " : " << std::endl;
}
void gun::draw(RenderWindow& window)
{
	window.draw(Gunshape);
	window.draw(Wallshape);
	if (Type == gunType::SpeedVariance)
	{
		window.draw(Bullets[0]);
	}
	if (Type == gunType::MultiBullets)
	{
		for (int j = 0; j < n; j++)
		{
			window.draw(Bullets[j]);
		}
	}
}
