#pragma once

#include <SFML/Graphics.hpp>
#include "interfaces.h"

class ball : public object {
public:
	ball();
	virtual ~ball();

	void set_position(const sf::Vector2f in_position);
	size_t get_player_idx() const { return m_player_idx; }

	virtual void update(float delta_time) override;
	virtual void draw(sf::RenderWindow &in_window) override;

	virtual bool intersect(object *in_obj) override { return false; }
	virtual void on_intersect() override {}

	bool is_sticked = true;
	float m_cur_speed = 500.f;
private:
	size_t m_player_idx = 0;
	sf::CircleShape m_shape;
};