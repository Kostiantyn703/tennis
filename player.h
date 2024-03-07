#pragma once

#include <SFML/Graphics.hpp>
#include "interfaces.h"

using shapes = std::vector<sf::RectangleShape>;

struct visual {
	float	m_padding = 1.f;
	float	m_side_size = 20.f;
	size_t	m_shape_count = 5;

	shapes	m_shapes;

	void init(const sf::Vector2f &in_pos);
};

class player : public icontrollable {
public:
	player(sf::Vector2f in_pos);
	~player();

	void draw(sf::RenderWindow &in_window);
	void update(float in_delta_time);

	const sf::Vector2f &get_position() const { return m_position; }
	virtual void set_movement(int in_val) override { m_cur_speed = m_max_speed * in_val; }

private:
	visual m_visual;
	sf::Vector2f m_position;
	float m_cur_speed = 0.f;
	float m_max_speed = 400.f;
};
