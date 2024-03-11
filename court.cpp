#include "court.h"
#include "controller.h"
#include "defs.h"

border::border(const sf::Vector2f & in_pos, const sf::Vector2f &in_size) {
	m_type = object_type::OT_BORDER;
	m_shape.setPosition(in_pos);
	m_shape.setSize(in_size);
}

void border::draw(sf::RenderWindow &in_window) {
	in_window.draw(m_shape);
}

void border::update(float delta_time) {}

court::court() {}

court::~court() {
	for (objects::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		delete *it;
	}
	m_objects.clear();
}

void court::init() {
	sf::Vector2f ball_pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);
	ball *cur_ball = new ball;
	cur_ball->set_position(ball_pos);
	m_objects.push_back(cur_ball);

	sf::Vector2f border_size(WINDOW_WIDTH, BORDER_OFFSET);

	border *upper_border = new border(sf::Vector2f(0.f, 0.f), border_size);
	m_objects.push_back(upper_border);

	border *lower_border = new border(sf::Vector2f(0.f, WINDOW_HEIGHT - BORDER_OFFSET), border_size);
	m_objects.push_back(lower_border);
}

void court::init_player(controller &out_controller) {
	sf::Vector2f player_one_pos(50.f, WINDOW_HEIGHT * 0.25f);
	player *cur_player = new player(player_one_pos);

	out_controller.set_owner(*cur_player);
	m_objects.push_back(cur_player);
}

void court::update(float delta_time) {
	for (objects::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		(*it)->update(delta_time);
	}
}
