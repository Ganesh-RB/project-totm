#include "stdafx.h"
#include "Data.h"
#include "Obstacles/Obstacle.h"
#include "Obstacles/gun.h"
#include "Obstacles/Dragon.h"
#include "Obstacles/pufferfish.h"
#include "Obstacles/teleporter.h"
#include "Obstacles/spring.h"

bool Data::read(std::vector<Data>& data)
{


	char filename[] = "data.txt"; //temperory
	size_t temp_var1, temp_var2, temp_var3, temp_var4;
	float f_var1, f_var2;
	size_t  N, size;

	std::ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
	{
		fin.close();
		return false;

	}

	while (!fin.eof())
	{
		if (fin.eof())
		{
			return true;
		}
			

		Data* data_p = new Data;

		fin >> temp_var1;
		data_p->level_no = temp_var1;
		fin >> temp_var1 >> temp_var2;
		data_p->Playerposition.x = temp_var1;
		data_p->Playerposition.y = temp_var2;




		fin >> size;
		for (size_t i = 0; i < size; i++)
		{
			fin >> temp_var1 >> temp_var2;
			fin >> temp_var3 >> temp_var4;
			data_p->wall_cordinates_sing.push_back(std::pair<sf::Vector2u,std::pair<int,int>>(sf::Vector2u(temp_var1, temp_var2), std::pair<int,int>(temp_var3, temp_var4)));
		}


		fin >> N;
		for (size_t j = 0; j < N; j++)
		{
			std::vector<sf::Vector2u> temp_vec;
			fin >> size;
			for (size_t i = 0; i < size; i++)
			{
				fin >> temp_var1 >> temp_var2;
				temp_vec.push_back(sf::Vector2u(temp_var1, temp_var2));
			}

			data_p->wall_cordinates_mult.push_back(temp_vec);
		}

		fin >> size;
		for (size_t i = 0; i < size; i++)

		{
			fin >> f_var1 >> f_var2;
			data_p->marker_pos_sing.push_back(sf::Vector2f(f_var1, f_var2));
		}


		fin >> N;
		for (size_t j = 0; j < N; j++)
		{
			std::vector<sf::Vector2f>* temp_vec=new std::vector<sf::Vector2f>;
			fin >> size;
			for (size_t i = 0; i < size; i++)
			{
				fin >> f_var1 >> f_var2;
				temp_vec->push_back(sf::Vector2f(f_var1, f_var2));
			}

			data_p->marker_pos_mult.push_back(*temp_vec);
			delete temp_vec;
		}


		fin >> N;
		for (size_t j = 0; j < N; j++)
		{
			fin >> temp_var1;
			fin >> size;

			switch (temp_var1)
			{
			case int(Obstacle::obstacle_type::Gun) :
				gun::read(fin, *data_p, size);
				break;
			case int(Obstacle::obstacle_type::Dragon) :
				Dragon::read(fin, *data_p, size);
				break;
			case int(Obstacle::obstacle_type::Teleporter) :
				teleporter::read(fin, *data_p, size);
				break;
			case int(Obstacle::obstacle_type::Pufferfish) :
				pufferfish::read(fin, *data_p, size);
				break;
			case int(Obstacle::obstacle_type::Spring) :
				spring::read(fin, *data_p, size);
			default:
				break;
			}
		}

		data.push_back(*data_p);

		delete data_p;

		if (fin.eof())
		{
#if defined(_DEBUG)
			std::cout << "eof reached\n";
#endif
			fin.close();
			return true;
		}

	}

	fin.close();

	return true;
}
