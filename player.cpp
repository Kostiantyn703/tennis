#include "player.h"
#include <iostream>
#include "court.h"

void visual::init(const sf::Vector2f &in_pos) {
	sf::Vector2f cur_pos = in_pos;
	sf::Vector2f size = sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT);
	for (size_t i = 0; i < PADDLE_SHAPE_COUNT; ++i) {
		sf::RectangleShape shape(size);
		shape.setPosition(cur_pos);
		m_shapes.push_back(shape);

		cur_pos.y += PADDLE_HEIGHT;
		cur_pos.y += PADDLE_PADDING;
	}
}

player::player(const sf::Vector2f &in_pos) {
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
	sf::Vector2f offset(0.f, m_cur_speed * in_delta_time);
	move(offset);
	set_position(m_position);
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

bool player::on_intersect(const sf::FloatRect &in_rect, int &out_idx) {
	for (int i = 0; i < PADDLE_SHAPE_COUNT; ++i) {
		if (m_visual.m_shapes[i].getGlobalBounds().intersects(in_rect)) {
			out_idx = i;
			return true;
		}
	}
	return false;
}

void player::launch() {
	if (m_ball_slot) {
		m_ball_slot->is_sticked = false;
		m_ball_slot = nullptr;
	}
}

void player::set_position(const sf::Vector2f &in_pos) {
	m_position = in_pos;
	sf::Vector2f cur_pos = in_pos;
	for (shapes::iterator it = m_visual.m_shapes.begin(); it != m_visual.m_shapes.end(); ++it) {
		it->setPosition(cur_pos);
		cur_pos.y += PADDLE_HEIGHT;
		cur_pos.y += PADDLE_PADDING;
	}
}

void player::move(sf::Vector2f &in_offset) {
	if ((m_position.y + abs(in_offset.y) - m_position.y) < 0.001f) {
		is_moving = false;
	}
	if ((m_position.y + abs(in_offset.y) - m_position.y) > 0.001f) {
		is_moving = true;
	}
	std::cout << "Offset " << in_offset.x << in_offset.y << std::endl;

	for (shapes::iterator it = m_visual.m_shapes.begin(); it != m_visual.m_shapes.end(); ++it) {
		it->move(in_offset);
	}
	m_position += in_offset;
}
