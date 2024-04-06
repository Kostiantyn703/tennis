#pragma once

#include <SFML/Graphics.hpp>
#include "interfaces.h"
#include "defs.h"

using shapes = std::vector<sf::RectangleShape>;

struct visual {
	shapes	m_shapes;

	void init(const sf::Vector2f &in_pos);
};

class ball;

class player : public object, public icontrollable {
public:
	player(const sf::Vector2f &in_pos);
	~player();

	virtual void draw(sf::RenderWindow &in_window) override;
	virtual void update(float in_delta_time) override;

	virtual bool intersect(object *in_obj) override;
	bool on_intersect(const sf::FloatRect &in_rect, int &out_idx);

	virtual void set_movement(int in_val) override { m_cur_speed = PLAYER_MAX_SPEED * in_val; }
	virtual void launch() override;

	size_t get_player_id() const { return m_player_id; }
	void set_player_id(size_t in_id) { m_player_id = in_id; }

	const sf::Vector2f &get_position() const { return m_position; }
	void set_position(const sf::Vector2f &in_pos);

	virtual void on_set_position() override {
		set_position(m_position);
	}

	void move(sf::Vector2f &in_offset);

private:
	size_t m_player_id;
	visual m_visual;
	float m_cur_speed = 0.f;
};
