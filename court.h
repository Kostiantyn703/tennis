#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "interfaces.h"
#include "player.h"
#include "ball.h"

using objects = std::vector<object*>;

class controller;

class border : public object {
public:
	border(const sf::Vector2f &in_pos, const sf::Vector2f &in_size);
	virtual ~border() {}

	virtual void draw(sf::RenderWindow &in_window) override;
	virtual void update(float delta_time) override;

private:
	sf::RectangleShape m_shape;
};

class court {
public:
	court();
	~court();

	void init();
	void init_player(controller &out_controller);

	void update(float delta_time);

	const objects &get_objects() const { return m_objects; }

private:
	objects m_objects;
};
