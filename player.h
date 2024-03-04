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
	player(sf::Vector2f in_pos);
	~player();

	void draw(sf::RenderWindow &in_window);
	void update(float in_delta_time);

	const sf::Vector2f &get_position() const { return m_position; }
	void set_direction(int in_val) { m_direction = in_val; }

private:
	visual m_visual;
	sf::Vector2f m_position;
	float m_speed = 0.f;
	int m_direction = 0;
};
