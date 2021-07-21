#pragma once
#include "state.h"
class dummy_state : public state
{
public:
	enum code_types { Destructed = -2, Paused, Constructed, Initialized_or_running };

	int& state_int;
	dummy_state(int& test_var);

	virtual ~dummy_state();

	void init() override;

	void pollevents() override;

	void update(float& deltatime) override;
	void render() override;

	void start() override;
	void pause() override;

};

