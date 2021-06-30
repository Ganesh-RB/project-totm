#include "..\stdafx.h"
#include "spike.h"

spike::spike(sf::Vector2u Spike_Position)
	:m_Spikes_Active{ false }, m_Spike_Box{ sf::FloatRect(11U * PlayerSize.x,17U * PlayerSize.y,PlayerSize.x,-PlayerSize.y / 2) },
	m_Alive{ true }, m_Time{ 0 }, m_Spikes_Render{ false }, m_Spike_Size{ sf::Vector2f(1.f, PlayerSize.y / 2) }, m_Spike_Number{ 15 }

{
	m_Spike_Position = sf::Vector2f(Spike_Position.x*PlayerSize.x, Spike_Position.y*PlayerSize.y);
	Initialize_Spike_Wall();
	Initialize_Spikes();
}

void spike::Initialize_Spike_Wall()
{
	m_Spike_Wall.resize(m_Spike_Number);

	for (int i = 0; i < 15; i++)
	{
		m_Spike_Wall[i].setSize(m_Spike_Size);
		m_Spike_Wall[i].setPosition(m_Spike_Position.x + (i * 2), m_Spike_Position.y);
		m_Spike_Wall[i].setFillColor(sf::Color::Red);
	}
}

void spike::Initialize_Spikes()
{
	m_Spikes.resize(m_Spike_Number);

	for (int i = 0; i < 15; i++)
	{
		m_Spikes[i].setSize(m_Spike_Size);
		m_Spikes[i].setPosition(m_Spike_Position.x + (i * 2), m_Spike_Position.y - PlayerSize.y / 2);
		m_Spikes[i].setFillColor(sf::Color::Red);
	}
}

void spike::UpdateSpikes(const sf::FloatRect& PlayerRect, float* dt)
{
	this->m_Player_Rect = PlayerRect;


	if (m_Player_Rect.intersects(m_Spike_Box))
	{
		m_Spikes_Active = true;
	}

	if (m_Spikes_Active)
	{
		m_dt = *dt;
		m_Time += m_dt;

		if (m_Time > 0.5f)
		{						
			m_Spikes_Render = true;

			if (m_Player_Rect.intersects(m_Spike_Box))
			{
				m_Alive = false;
			}

			else
			{
				if (m_Time > 1.5f)
				{	
					m_Spikes_Render = false;
					m_Spikes_Active = false;
					m_Time = 0;
				}
				
			}
		}
	}
}

bool spike::GetAlive()
{
	return m_Alive;
}

void spike::RenderSpikes(sf::RenderWindow* Window)
{ 

	if (!m_Spikes_Render)
	{
		for (int i = 0; i < 15; i++)
		{
			Window->draw(m_Spike_Wall[i]);
		}
	}
	
	if (m_Spikes_Render)
	{
		for (int i = 0; i < 15; i++)
		{
			Window->draw(m_Spikes[i]);
		}
	}
}




