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

	size_t get_idx() const { return m_idx; }
	void set_idx(size_t in_idx) { m_idx = in_idx; }

	const sf::Vector2f &get_position() const { return m_position; }
	void set_position(const sf::Vector2f &in_pos);

	void move(sf::Vector2f &in_offset);

	ball *m_ball_slot = nullptr;
	// TODO: temp for test
	player *m_player_slot = nullptr;
private:
	size_t m_idx;
	visual m_visual;
	sf::Vector2f m_position;
	float m_cur_speed = 0.f;
};
