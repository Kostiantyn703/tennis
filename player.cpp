#include "player.h"

#include <iostream>

#include "court.h"

void visual::init(const sf::Vector2f &in_pos) {
	sf::Vector2f cur_pos = in_pos;
	sf::Vector2f size = sf::Vector2f(m_side_size, m_side_size);
	for (size_t i = 0; i < m_shape_count; ++i) {
		sf::RectangleShape shape(size);
		shape.setPosition(cur_pos);
		m_shapes.push_back(shape);

		cur_pos.y += m_side_size;
		cur_pos.y += m_padding;
	}
}

player::player(const sf::Vector2f &in_pos) {
	m_type = object_type::OT_PADDLE;
	m_position = in_pos;
	m_visual.init(m_position);
}

player::~player() {}

void player::draw(sf::RenderWindow &in_window) {
	for (shapes::iterator it = m_visual.m_shapes.begin(); it != m_visual.m_shapes.end(); ++it) {
		in_window.draw(*it);
	}
}

void player::update(float in_delta_time) {
	for (shapes::iterator it = m_visual.m_shapes.begin(); it != m_visual.m_shapes.end(); ++it) {
		sf::Vector2f offset(0.f, m_cur_speed * in_delta_time);
		it->move(offset);
	}
	m_position.y += m_cur_speed * in_delta_time;
	if (m_ball_slot) {
		m_ball_slot->set_position(m_position);
	}
}

bool player::intersect(object *in_obj) {
	if (border *bord = dynamic_cast<border*>(in_obj)) {
		upper_block = m_visual.m_shapes.begin()->getGlobalBounds().intersects(bord->get_shape().getGlobalBounds());
		lower_block = (m_visual.m_shapes.end() - 1)->getGlobalBounds().intersects(bord->get_shape().getGlobalBounds());
		if (upper_block || lower_block) {
			set_movement(0);
			return true;
		}
	}
	return false;
}

void player::on_intersect() {

}

void player::launch() {
	if (m_ball_slot) {
		m_ball_slot->is_sticked = false;
		m_ball_slot = nullptr;
	}
}
