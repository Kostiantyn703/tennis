#include "ball.h"
#include "defs.h"
#include "game.h"

constexpr float PADDLE_OFFSET_X = 10.f;
constexpr float PADDLE_OFFSET_Y = 45.f;

ball::ball() {
	m_shape.setRadius(10.f);
}

ball::~ball() {}

void ball::set_position(const sf::Vector2f in_position) {
	sf::Vector2f new_pos = in_position;
	// TODO: also depending on player idx set initial direction
	m_player_idx == 0 ? (new_pos.x += PADDLE_OFFSET_X) : (new_pos.x -= PADDLE_OFFSET_X);
	new_pos.y += PADDLE_OFFSET_Y;

	m_shape.setPosition(new_pos);
}

void ball::update(float delta_time) {
	if (!is_sticked) {
		float delta_x = m_cur_speed * calculate_cosine(m_cur_direction) * delta_time;
		float delta_y = m_cur_speed * caculate_sine(m_cur_direction) * delta_time;
		sf::Vector2f offset(delta_x, delta_y);
		m_shape.move(offset);
	}
}

void ball::draw(sf::RenderWindow &in_window) {
	in_window.draw(m_shape);
}

bool ball::intersect(object *in_obj) {
	if (border *bord = dynamic_cast<border*>(in_obj)) {
		if (bord->get_shape().getGlobalBounds().intersects(m_shape.getGlobalBounds())) {
			set_direction(-m_cur_direction);
			return true;
		}
		return false;
	}
	if (player *paddle = dynamic_cast<player*>(in_obj)) {
		if (paddle->on_intersect(m_shape.getGlobalBounds())) {
			set_direction(-m_cur_direction + PLANE_ANGLE);
			return true;
		}
	}
	return false;
}
