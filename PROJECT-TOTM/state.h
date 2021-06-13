#pragma once




class state
{
public:
	state() {};
	virtual ~state() {};

	virtual void init() = 0;
	virtual void pollevents() = 0;
	virtual void update(float& deltatime) = 0;
	virtual void render() = 0;

	virtual void pause() {};
	virtual void start() {};
};

