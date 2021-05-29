#include "player.h"
#include <iostream>
enum move_dir_no { MOVE_NULL, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN, MOVE_UP };
void player::initvariables()
{
	this->movementspeed = 15.0f;
	moving = false;
	movedirection = MOVE_NULL;
}

const void player::initshape()
{
	this->shape.setFillColor(sf::Color::Color(0, 255, 0, 255));
	this->shape.setSize(sf::Vector2f(30.f, 30.f));

}



player::player(float  _x, float  _y)
{
	this->shape.setPosition(_x, _y);
	this->initshape();
	this->initvariables();
}

player::~player()
{
}

sf::Vector2f player::getcoord()
{
	sf::Vector2f result = shape.getPosition();
	return result;
}

void player::getendtrail(int num)
{
	sf::FloatRect pb = this->shape.getGlobalBounds();
	switch (num)
	{
	case MOVE_LEFT:
		end_trail = sf::Vector2f(pb.left, pb.top);
		break;
	case MOVE_RIGHT:
		end_trail = sf::Vector2f(pb.left + pb.width, pb.top);
		break;
	case MOVE_DOWN:
		end_trail = sf::Vector2f(pb.left, pb.top + pb.height);
		break;
	case MOVE_UP:
		end_trail = sf::Vector2f(pb.left, pb.top);
		break;
	default:
		printf("error in player::getendtrail \n");
		break;
	}
}

void player::updateinput()
{
	if (moving == false) {
		sf::FloatRect pb = this->shape.getGlobalBounds(); //pb is for playerbounds
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			moving = true;
			movedirection = MOVE_LEFT;
			start_trail = sf::Vector2f(pb.left + pb.width, pb.top);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			moving = true;
			movedirection = MOVE_RIGHT;
			start_trail = sf::Vector2f(pb.left, pb.top);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			moving = true;
			movedirection = MOVE_DOWN;
			start_trail = sf::Vector2f(pb.left, pb.top);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			moving = true;
			movedirection = MOVE_UP;
			start_trail = sf::Vector2f(pb.left, pb.top + pb.height);
		}
	}
	if (moving == true)
	{
		switch (movedirection)
		{
		case MOVE_LEFT:
			this->shape.move(-this->movementspeed*dt*time_mult, 0.f);
			break;
		case MOVE_RIGHT:
			this->shape.move(this->movementspeed*dt*time_mult, 0.f);
			break;
		case MOVE_DOWN:
			this->shape.move(0.f, this->movementspeed*dt*time_mult);
			break;
		case MOVE_UP:
			this->shape.move(0.f, -this->movementspeed*dt*time_mult);
			break;
		default:
			printf("error in player movement direction variable \n");
			break;
		}
		getendtrail(movedirection);
	}
}

void player::updatewindowcollision(sf::RenderTarget * target)
{
	bool flag = 0;
	sf::FloatRect playerbounds = this->shape.getGlobalBounds();
	if (playerbounds.left < 0.f) {
		this->shape.setPosition(0.f, playerbounds.top);
		flag = 1;
	}
	else if (playerbounds.left + playerbounds.width > target->getSize().x) {
		this->shape.setPosition(target->getSize().x - playerbounds.width, playerbounds.top);
		flag = 1;
	}
	playerbounds = this->shape.getGlobalBounds();
	if (playerbounds.top < 0.f) {
		this->shape.setPosition(playerbounds.left, 0.f);
		flag = 1;
	}
	else if (playerbounds.top + playerbounds.height > target->getSize().y) {
		this->shape.setPosition(playerbounds.left, target->getSize().y - playerbounds.height);
		flag = 1;
	}
	if (flag == 1) {
		getendtrail(movedirection);
		moving = false;
		movedirection = MOVE_NULL;
		if ((fabs(start_trail.x - end_trail.x) > playerbounds.width + 5.f) || (fabs(start_trail.y - end_trail.y) > playerbounds.height + 5.f))
		{
			trails.push_back(curr_trail(&start_trail, &end_trail));
			//std::cout << "number of elements in trail vector are " << trails.size() << std::endl;
		}
	}
}
void player::update_collision(sf::RectangleShape* object) {
	bool flag1 = 0;
	sf::FloatRect ob = object->getGlobalBounds();
	sf::FloatRect pb = this->shape.getGlobalBounds();
	switch (movedirection) {
	case MOVE_LEFT:
		if ((pb.top >= ob.top - 5.f) && (pb.top + pb.height <= ob.top + ob.height + 5.f)) {
			if (!(pb.left < ob.left)) {
				if (pb.left < ob.left + ob.width) {
					flag1 = 1;
					this->shape.setPosition(ob.left + ob.width, pb.top);
				}
			}
		}
		break;
	case MOVE_RIGHT:
		if ((pb.top >= ob.top - 5.f) && (pb.top + pb.height <= ob.top + ob.height + 5.f)) {
			if (!(pb.left + pb.width > ob.left + ob.width)) {
				if (pb.left + pb.width > ob.left) {
					flag1 = 1;
					this->shape.setPosition(ob.left - pb.width, pb.top);
				}
			}
		}
		break;
	case MOVE_DOWN:
		if ((pb.left >= ob.left - 5.f) && (pb.left + pb.width <= ob.left + ob.width + 5.f)) {
			if (!(pb.top > ob.top + ob.height)) {
				if (pb.top + pb.height > ob.top) {
					flag1 = 1;
					this->shape.setPosition(pb.left, ob.top - pb.height);
				}
			}
		}
		break;
	case MOVE_UP:
		if ((pb.left >= ob.left - 5.f) && (pb.left + pb.width <= ob.left + ob.width + 5.f)) {
			if (!(pb.top + pb.height < ob.top)) {
				if (pb.top < ob.top + ob.height) {
					flag1 = 1;
					this->shape.setPosition(pb.left, ob.top + ob.height);
				}
			}
		}
		break;
	default:
		flag1 = 0;
	}
	if (flag1 == 1) {
		getendtrail(movedirection);
		moving = false;
		movedirection = MOVE_NULL;
		if ((fabs(start_trail.x - end_trail.x) > pb.width*1.2) || (fabs(start_trail.y - end_trail.y) > pb.height*1.2))
		{
			trails.push_back(curr_trail(&start_trail, &end_trail));
			//std::cout << "number of elements in trail vector are " << trails.size() << std::endl;
		}
	}
}

void player::update(sf::RenderTarget* target, float* _dt, float* _time_mult)
{
	dt = *_dt;
	time_mult = *_time_mult;
	this->updateinput();
	this->updatewindowcollision(target);
}

void player::render(sf::RenderTarget * target)
{
	if (moving == true) { target->draw(curr_trail(&start_trail, &end_trail)); }
	for (auto i : this->trails)
	{
		target->draw(i);
	}
	target->draw(this->shape);

}

sf::RectangleShape player::curr_trail(sf::Vector2f* start, sf::Vector2f* end)
{
	sf::RectangleShape result;
	result.setFillColor(sf::Color::Color(150, 0, 150, 255));
	float init_pt = fabs(end->x - start->x) > 20 ? end->x - start->x : 30.f;
	float end_pt = fabs(end->y - start->y) > 20 ? end->y - start->y : 30.f;
	result.setSize(sf::Vector2f(init_pt, end_pt));
	result.setPosition(*start);
	return result;

}