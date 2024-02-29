#pragma once

#include <SFML/Graphics.hpp>

using shapes = std::vector<sf::RectangleShape>;

struct visual {
	float	m_padding = 1.f;
	float	m_side_size = 20.f;
	size_t	m_shape_count = 5;

	shapes	m_shapes;

	void init(const sf::Vector2f &in_pos);
};

class player {
public:
	player();
	~player();

	const sf::Vector2f &get_position() const { return m_position; }

	void draw(sf::RenderWindow &in_window);
	void update(float in_delta_time);

private:
	visual m_visual;
	sf::Vector2f m_position;
};
