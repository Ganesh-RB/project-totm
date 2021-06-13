#pragma once

#include <stack>
#include <memory>
#include "state.h"


class stateman
{
private:
	std::stack<std::unique_ptr<state>> m_statestack;
	std::unique_ptr<state> m_newstate;

	bool m_add;
	bool m_replace;
	bool m_remove;

public:
	stateman();
	~stateman();
	
	void Add(std::unique_ptr<state> toAdd, bool replace = false);
	void Popcurrent();
	void ProcessStatechange();
	std::unique_ptr<state>& Getcurrent();
};


