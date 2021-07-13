#ifndef CONTEXT_H
#define CONTEXT_H

#include "stateman.h"
#include "asset_holder.h"
////////////////////////////////////////////////////////////
/// \struct 
///\brief contains all info needed for state implementation
/// 
/// \param m_states unique ptr to statestack
/// \param m_window unique ptr to a window
///
////////////////////////////////////////////////////////////
struct context
{
	std::unique_ptr<stateman> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::unique_ptr<asset_holder> m_assets;

	context()
	{
		m_states = std::make_unique<stateman>();
		m_window = std::make_unique<sf::RenderWindow>();
		m_assets = std::make_unique<asset_holder>();
	}
};

#endif