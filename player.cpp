#include "player.h"

#include <iostream>

player::player() {
	m_position.x = 200.f;
	m_position.y = 200.f;
	sf::Vector2f size(100.f, 100.f);
	m_shape = sf::RectangleShape(size);
	m_shape.setPosition(m_position);

	std::cout << "Origin x = " << m_shape.getOrigin().x << " y = " << m_shape.getOrigin().y << std::endl;
	std::cout << "Position x = " << m_shape.getPosition().x << " y = " << m_shape.getPosition().y << std::endl;

}

player::~player() {

}