#include "ball.h"

constexpr float PADDLE_OFFSET_X = 20.f;
constexpr float PADDLE_OFFSET_Y = 45.f;

ball::ball() {
	m_type = object_type::OT_BALL;
	m_shape.setRadius(10.f);
}

ball::~ball() {}

void ball::set_position(const sf::Vector2f in_position) {
	sf::Vector2f new_pos = in_position;
	m_player_idx == 0 ? (new_pos.x += PADDLE_OFFSET_X) : (new_pos.x -= PADDLE_OFFSET_X);
	new_pos.y += PADDLE_OFFSET_Y;

	m_shape.setPosition(new_pos);
}

void ball::update(float delta_time) {
	if (!is_sticked) {
		sf::Vector2f offset(m_cur_speed * delta_time, 0.f);
		m_shape.move(offset);
	}
}

void ball::draw(sf::RenderWindow &in_window) {
	in_window.draw(m_shape);
}
