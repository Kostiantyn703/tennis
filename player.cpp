#include "player.h"

#include <iostream>

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

player::player() {
	m_position.x = 50.f;
	m_position.y = 200.f;
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
		float cur_x = it->getPosition().x;
		float cur_y = it->getPosition().y;
		cur_y += m_speed *in_delta_time;
		sf::Vector2f new_pos(cur_x, cur_y);

		it->setPosition(new_pos);
	}
}

