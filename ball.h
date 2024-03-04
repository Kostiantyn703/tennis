#pragma once

#include <SFML/Graphics.hpp>

class ball {
public:
	ball();
	~ball();

	void set_position(const sf::Vector2f in_position);
	size_t get_player_idx() const { return m_player_idx; }

	void update(float delta_time);
	void draw(sf::RenderWindow &in_window);

private:
	sf::CircleShape m_shape;
	sf::Vector2f m_position;

	float m_paddle_offset_x = 20.f;
	float m_paddle_offset_y = 50.f;

	size_t m_player_idx = 0;
};