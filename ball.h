#pragma once

#include <SFML/Graphics.hpp>
#include "interfaces.h"

class ball : public object {
public:
	ball();
	virtual ~ball();

	virtual void on_set_position() override{
		set_position(m_position, 0, false);
	}

	void set_position(const sf::Vector2f in_position, size_t in_player_id, bool offset = true);
	const sf::CircleShape &get_shape() const { return m_shape; }

	void set_direction(float in_dir) { m_cur_direction = in_dir; }

	virtual void update(float delta_time) override;
	virtual void draw(sf::RenderWindow &in_window) override;

	virtual bool intersect(object *in_obj) override;

	bool is_sticked = true;
	
private:
	float m_cur_direction = 45.f;
	float m_cur_speed = 500.f;

	sf::CircleShape m_shape;
};