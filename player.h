#pragma once

#include <SFML/Graphics.hpp>
#include "interfaces.h"
#include "defs.h"

using shapes = std::vector<sf::RectangleShape>;

struct visual {
	float	m_padding = 1.f;
	float	m_side_size = 20.f;
	size_t	m_shape_count = 5;

	shapes	m_shapes;

	void init(const sf::Vector2f &in_pos);
};

class player : public object, public icontrollable {
public:
	player(const sf::Vector2f &in_pos);
	~player();

	virtual void draw(sf::RenderWindow &in_window) override;
	virtual void update(float in_delta_time) override;

	virtual void intersect(object *in_obj) override;
	virtual void on_intersect() override;

	const sf::Vector2f &get_position() const { return m_position; }
	virtual void set_movement(int in_val) override { m_cur_speed = PLAYER_MAX_SPEED * in_val; }

private:
	visual m_visual;
	sf::Vector2f m_position;
	float m_cur_speed = 0.f;
};
