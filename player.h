#pragma once

#include <SFML/Graphics.hpp>

class player {
public:
	player();
	~player();

	const sf::RectangleShape &get_shape() const { return m_shape; }
	const sf::Vector2f &get_position() const { return m_position; }

private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
};
