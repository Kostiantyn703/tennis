#pragma once

#include <SFML/Graphics.hpp>

class ball {
public:
	ball();
	~ball();

	void set_position(const sf::Vector2f in_position);

	void update(float delta_time);
	void draw(sf::RenderWindow &in_window);

private:
	sf::CircleShape m_shape;
	sf::Vector2f m_position;
};
