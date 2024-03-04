#include "ball.h"

ball::ball() {
	m_shape.setRadius(10.f);
}

ball::~ball() {}

void ball::set_position(const sf::Vector2f in_position) {
	m_position = in_position;
	m_shape.setPosition(m_position);
}

void ball::update(float delta_time) {

}

void ball::draw(sf::RenderWindow &in_window) {
	in_window.draw(m_shape);
}
