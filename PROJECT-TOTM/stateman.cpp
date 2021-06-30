#include "stdafx.h"
#include "stateman.h"

stateman::stateman() : m_add(false), m_replace(false), m_remove(false)
{
}

stateman::~stateman()
{
}

void stateman::Add(std::unique_ptr<state> toAdd, bool replace)
{
	m_add = true;
	m_newstate = std::move(toAdd);

	m_replace = replace;
}

void stateman::Popcurrent()
{
	m_remove = true;
}

void stateman::ProcessStatechange()
{
	if (m_remove && (!m_statestack.empty()))
	{
		m_statestack.pop();

		if (!m_statestack.empty())
		{
			m_statestack.top()->start();
		}

		m_remove = false;
	}

	if (m_add)
	{
		if (m_replace && (!m_statestack.empty()))
		{
			m_statestack.pop();
			m_replace = false;
		}

		if (!m_statestack.empty())
		{
			m_statestack.top()->pause();
		}

		m_statestack.push(std::move(m_newstate));
		m_statestack.top()->init();
		m_statestack.top()->start();
		m_add = false;
	}
}

std::unique_ptr<state>& stateman::Getcurrent()
{
	return m_statestack.top();
}