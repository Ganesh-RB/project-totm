#include "stdafx.h"
#include "dummy_state.h"

dummy_state::dummy_state(int & test_var) :state_int(test_var)
{
	state_int = 0;
}

dummy_state::~dummy_state()
{
	state_int = -2;
}

void dummy_state::init()
{
}

void dummy_state::pollevents()
{
}

void dummy_state::update(float & deltatime)
{
}

void dummy_state::render()
{
}

void dummy_state::start()
{
	state_int = 1;
}

void dummy_state::pause()
{
	state_int = -1;
}
