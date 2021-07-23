#include "stdafx.h"
#include "player.h"

void player::initvariables()
{
	movementspeed = BASE_SIZE / 2.f;
	moving = false;
	previous_moving = false;
	movedirection = move_dir_no::MOVE_NULL;
	all_grids_colored = false;
	display_markers = false;
	marker_temp.setFillColor(sf::Color::Yellow);
	marker_temp.setSize(sf::Vector2f(2.f, 2.f));
	marker_temp.setOrigin(sf::Vector2f(1.f, 1.f));
	for (int i = 0; i < 6; i++) {
		if (i < 4){
			display_frame[i] = sf::IntRect(30 * i, 0, 30, 30);
		}
		else {
			display_frame[i] = sf::IntRect(90, 0, 30 * (i - 2), 30);
		}
	}
	last_moving_direction = move_dir_no::MOVE_DOWN;
	player_sprite.setTexture(m_assets.get_texture(asset_holder::group_member_name::OJJAS, asset_holder::ojjas_textures::PLAYER));
	player_sprite.setScale(BASE_SIZE / 30.f, BASE_SIZE / 30.f);
	player_sprite.setTextureRect(display_frame[0]);
	player_sprite.setPosition(shape.getPosition());
	anim_dir = 1;
	anim_timer = 0.f;
	trail_timer = 0.f;
	spring_flag = false;
	dead = false;
	end_flag = false;
}

const void player::initshape()
{
	this->shape.setSize(sf::Vector2f(BASE_SIZE, BASE_SIZE));
}

bool player::level_complete()
{
	return  all_grids_colored;
}

void player::add_marker_chain(const std::vector<sf::Vector2f>& points)
{
	sf::Vector2f chain_point=(points.size()>0)? points[0]:sf::Vector2f(0.f,0.f);
	for (int i = 1; i < points.size(); i++) {
		float max_y, max_x, min_y, min_x;
		if (points[i].x > chain_point.x) {
			max_x = points[i].x;
			min_x = chain_point.x;
		}
		else {
			max_x = chain_point.x;
			min_x = points[i].x;
		}
		if (points[i].y > chain_point.y) {
			max_y = points[i].y;
			min_y = chain_point.y;
		}
		else {
			max_y = chain_point.y;
			min_y = points[i].y;
		}

		while ((max_x - min_x >= 0.9f) || (max_y - min_y >= 0.9f)) {
			marker_temp.setPosition(sf::Vector2f(min_x*BASE_SIZE, min_y*BASE_SIZE));
			markers.push_back(marker_temp);
			min_x += (max_x - min_x >= 0.9f);
			min_y += (max_y - min_y >= 0.9f);
		}
		marker_temp.setPosition(sf::Vector2f(max_x*BASE_SIZE, max_y*BASE_SIZE));
		markers.push_back(marker_temp);
		chain_point = points[i];
	}
}

void player::add_marker_single(sf::Vector2f &pos)
{

	marker_temp.setPosition(sf::Vector2f(pos.x*BASE_SIZE, pos.y*BASE_SIZE));
	markers.push_back(marker_temp);
}



player::player(asset_holder* assets) :m_assets(*assets)
{
	this->shape.setPosition(BASE_SIZE*0, BASE_SIZE *0);
	this->initshape();
	this->initvariables();
	
}

player::~player()
{
}

void player::setPosition(const sf::Vector2u position)
{
	this->shape.setPosition(BASE_SIZE * position.x, BASE_SIZE * position.y);
}

void player::set_player_dead()
{
	dead = true;
}

sf::Vector2f player::getcoord()
{
	sf::Vector2f result = shape.getPosition();
	return result;
}

void player::get_end_trail(move_dir_no dir, sf::FloatRect pb)
{
	switch (dir)
	{
	case move_dir_no::MOVE_LEFT:
		end_trail = sf::Vector2f(pb.left, pb.top);
		break;
	case move_dir_no::MOVE_RIGHT:
		end_trail = sf::Vector2f(pb.left + pb.width, pb.top);
		break;
	case move_dir_no::MOVE_DOWN:
		end_trail = sf::Vector2f(pb.left, pb.top + pb.height);
		break;
	case move_dir_no::MOVE_UP:
		end_trail = sf::Vector2f(pb.left, pb.top);
		break;
	default:
		printf("error in player::get_end_trail \n");
		break;
	}
}

void player::update_animation(float _dt)
{
	if(!dead){
		anim_timer += 180 * anim_dir* _dt;
		if (anim_timer > 60.f) { anim_dir = -1; }
		if (anim_timer < 0.f) { anim_dir = 1; }
		
		if (moving && previous_moving) {
			trail_timer += movementspeed * 24.f*_dt;
			if (trail_timer > 60.f) { player_sprite.setTextureRect(display_frame[5]); }
			else if (trail_timer > 30.f) { player_sprite.setTextureRect(display_frame[4]); }
			else { player_sprite.setTextureRect(display_frame[3]); }

		}
		else {
			trail_timer = 0.f;
			if (anim_timer < 20.f) {
				player_sprite.setTextureRect(display_frame[0]);
			}
			else if (anim_timer < 40.f) {
				player_sprite.setTextureRect(display_frame[1]);

			}
			else { player_sprite.setTextureRect(display_frame[2]); }
		}
		float temp;
		switch (last_moving_direction)
		{
		case move_dir_no::MOVE_LEFT:
			temp = 90.f;
			
			break;
		case move_dir_no::MOVE_RIGHT:
			temp = -90.f;
			
			break;
		case move_dir_no::MOVE_UP:
			temp = 180.f;
			
			break;
		case move_dir_no::MOVE_DOWN:
			temp = 0.f;
			
			break;
		default:
			printf("ERROR::PLAYER::UPDATE_ANIMATION::invalid value of last_moving_direction\n");
			break;
		}
		temp += (moving&&previous_moving)*-90.f;
		player_sprite.setRotation(temp);
		switch (((((int)temp)/90)+4)%4) {
		case 0:
			player_sprite.setPosition(shape.getPosition());
			break;
		case 1:
			player_sprite.setPosition(shape.getPosition() + sf::Vector2f(BASE_SIZE, 0.f));
			break;
		case 2:
			player_sprite.setPosition(shape.getPosition() + sf::Vector2f(BASE_SIZE, BASE_SIZE));
			break;
		case 3:
			player_sprite.setPosition(shape.getPosition() + sf::Vector2f(0.f, BASE_SIZE));
			break;
		default:
			printf("ERROR::PLAYER::UPDATE_ANIMATION::temp not processed correctly\n");
			break;

		
		}
		
	}
	else {
		anim_timer += 6 * anim_dir* _dt;
		if (anim_timer > 60.f) { anim_dir = -1; }
		if (anim_timer < 0.f) { anim_dir = 1; }
		player_sprite.setTextureRect(display_frame[0]);
		switch ((int)anim_timer % 4) {
		case 0:
			player_sprite.setRotation(0.f);
			player_sprite.setPosition(shape.getPosition());
			break;
		case 1:
			player_sprite.setRotation(90.f);
			player_sprite.setPosition(shape.getPosition() + sf::Vector2f(BASE_SIZE, 0.f));
			break;
		case 2:
			player_sprite.setRotation(180.f);
			player_sprite.setPosition(shape.getPosition() + sf::Vector2f(BASE_SIZE, BASE_SIZE));
			break;
		case 3:
			player_sprite.setRotation(270.f);
			player_sprite.setPosition(shape.getPosition() + sf::Vector2f(0.f, BASE_SIZE));
			break;
		}
	}
}

void player::get_start_trail(move_dir_no dir,sf::FloatRect pb)
{
	switch (dir)
	{
	case move_dir_no::MOVE_LEFT:
		start_trail = sf::Vector2f(pb.left +pb.width, pb.top);
		break;
	case move_dir_no::MOVE_RIGHT:
		start_trail = sf::Vector2f(pb.left, pb.top);
		break;
	case move_dir_no::MOVE_DOWN:
		start_trail = sf::Vector2f(pb.left, pb.top );
		break;
	case move_dir_no::MOVE_UP:
		start_trail = sf::Vector2f(pb.left, pb.top+pb.width);
		break;
	default:
		printf("error in player::get_start_trail \n");
		break;
	}
}

void player::update_input_and_movement()
{
	if (!spring_flag) { previous_moving = moving; }
	spring_flag = false;
	if (moving == false) {
		sf::FloatRect pb = this->shape.getGlobalBounds(); //pb is for playerbounds
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			moving = true;
			movedirection = move_dir_no::MOVE_LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			moving = true;
			movedirection = move_dir_no::MOVE_RIGHT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			moving = true;
			movedirection = move_dir_no::MOVE_DOWN;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			moving = true;
			movedirection = move_dir_no::MOVE_UP;
		}
		if (moving) {
			last_moving_direction =movedirection;
			get_start_trail(movedirection, pb);
		}
	}
	if (moving == true)
	{
		float mov = (movementspeed*dt*time_mult > BASE_SIZE*0.8f) ? BASE_SIZE * 0.8f : movementspeed * dt*time_mult;
		switch (movedirection)
		{
		case move_dir_no::MOVE_LEFT:
			this->shape.move(-mov, 0.f);
			break;
		case move_dir_no::MOVE_RIGHT:
			this->shape.move(mov, 0.f);
			break;
		case move_dir_no::MOVE_DOWN:
			this->shape.move(0.f, mov);
			break;
		case move_dir_no::MOVE_UP:
			this->shape.move(0.f, -mov);
			break;
		default:
			printf("error in player movement direction variable \n");
			break;
		}
		get_end_trail(movedirection,shape.getGlobalBounds());
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
		get_end_trail(movedirection,shape.getGlobalBounds());
		moving = false;
		movedirection = move_dir_no::MOVE_NULL;
		if ((fabs(start_trail.x - end_trail.x) > playerbounds.width*1.2f) || (fabs(start_trail.y - end_trail.y) > playerbounds.height*1.2f))
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
	case move_dir_no::MOVE_LEFT:
		if ((pb.top >= ob.top - 5.f) && (pb.top + pb.height <= ob.top + ob.height + 5.f)) {
			if (!(pb.left + pb.width < ob.left+5.f)) {
				if (pb.left < ob.left + ob.width) {
					flag1 = 1;
					this->shape.setPosition(ob.left + ob.width, pb.top);
				}
			}
		}
		break;
	case move_dir_no::MOVE_RIGHT:
		if ((pb.top >= ob.top - 5.f) && (pb.top + pb.height <= ob.top + ob.height + 5.f)) {
			if (!(pb.left+5.f > ob.left + ob.width)) {
				if (pb.left + pb.width > ob.left) {
					flag1 = 1;
					this->shape.setPosition(ob.left - pb.width, pb.top);
				}
			}
		}
		break;
	case move_dir_no::MOVE_DOWN:
		if ((pb.left >= ob.left - 5.f) && (pb.left + pb.width <= ob.left + ob.width + 5.f)) {
			if (!(pb.top+5.f > ob.top + ob.height)) {
				if (pb.top + pb.height > ob.top) {
					flag1 = 1;
					this->shape.setPosition(pb.left, ob.top - pb.height);
				}
			}
		}
		break;
	case move_dir_no::MOVE_UP:
		if ((pb.left >= ob.left - 5.f) && (pb.left + pb.width <= ob.left + ob.width + 5.f)) {
			if (!(pb.top + pb.height < ob.top+5.f)) {
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
		get_end_trail(movedirection,shape.getGlobalBounds());
		moving = false;
		movedirection = move_dir_no::MOVE_NULL;
		if ((fabs(start_trail.x - end_trail.x) > pb.width*1.2f) || (fabs(start_trail.y - end_trail.y) > pb.height*1.2f))
		{
			m_assets.play_sound(asset_holder::group_member_name::OJJAS,asset_holder::ojjas_sounds::COLLIDE,50.f);
			trails.push_back(curr_trail(&start_trail, &end_trail));
			//std::cout << "number of elements in trail vector are " << trails.size() << std::endl;
		}
	}
}

void player::updatemarkers()
{
	if (markers.size() != 0) {
		markers.erase(std::partition(begin(markers), end(markers),
			[this](const auto &x) {return !x.getGlobalBounds().intersects(shape.getGlobalBounds()); }),
			end(markers));
	}
	else {
		if (end_flag == false) {
			end_flag = true;
			ending_movement.first = getcoord();
		}
		else {
			sf::FloatRect pb = this->shape.getGlobalBounds();
			ending_movement.second = getcoord();
			if((moving==false) ||((fabs(ending_movement.second.y - ending_movement.first.y) > (BASE_SIZE / 2) + marker_temp.getLocalBounds().width)
				|| (fabs(ending_movement.second.x - ending_movement.first.x) > (BASE_SIZE / 2) + marker_temp.getLocalBounds().width))) {
					if(moving==true){
					get_end_trail(movedirection,shape.getGlobalBounds());
					moving = false;
					movedirection = move_dir_no::MOVE_NULL;
					trails.push_back(curr_trail(&start_trail, &end_trail));
					//std::cout << "number of elements in trail vector are " << trails.size() << std::endl;
					}
			    all_grids_colored = true;
			}
		}
	}
}

void player::update(sf::RenderWindow* target, float* _dt, float* _time_mult)
{
	dt = *_dt;
	time_mult = *_time_mult;
	if(!level_complete()&& !dead){
		this->update_input_and_movement();
		this->updatewindowcollision(target);
		this->updatemarkers();
	}
	this->update_animation(dt);
	
}

void player::render(sf::RenderWindow * target)
{
	if (moving == true) { target->draw(curr_trail(&start_trail, &end_trail)); }
	for (const auto i : this->trails)
	{
		target->draw(i);
	}
	target->draw(this->player_sprite);
	if (display_markers)
		for (const auto i : this->markers)
		{
			target->draw(i);
		}
}

sf::RectangleShape player::curr_trail(sf::Vector2f* start, sf::Vector2f* end)
{
	sf::RectangleShape result;
	result.setFillColor(sf::Color(0, 100,255, 255));
	float init_pt = fabs(end->x - start->x) > BASE_SIZE*0.8f ? end->x - start->x : BASE_SIZE;
	float end_pt = fabs(end->y - start->y) > BASE_SIZE*0.8f ? end->y - start->y : BASE_SIZE;
	result.setSize(sf::Vector2f(init_pt, end_pt));
	result.setPosition(*start);
	return result;

}
