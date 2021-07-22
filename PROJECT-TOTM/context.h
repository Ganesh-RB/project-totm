#ifndef CONTEXT_H
#define CONTEXT_H

#include "stateman.h"
#include "asset_holder.h"
#include "Data.h"
////////////////////////////////////////////////////////////
/// \struct 
/// \brief contains all info needed for state implementation
/// 
/// \param m_states unique ptr to statestack
/// \param m_window unique ptr to a window
/// \param m_assets
/// \param m_level_no
/// \param m_data
///
////////////////////////////////////////////////////////////
struct context
{
	std::unique_ptr<stateman> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::unique_ptr<asset_holder> m_assets;
	std::unique_ptr<unsigned> m_level_no;
	std::unique_ptr<std::vector<Data>> m_data;
	
	context()
	{
		m_states = std::make_unique<stateman>();
		m_window = std::make_unique<sf::RenderWindow>();
		m_assets = std::make_unique<asset_holder>();
		m_level_no = std::make_unique<unsigned>(1u);
		m_data = std::make_unique<std::vector<Data>>();
	}
};

#endif