#pragma once

#include <SFML/Graphics.hpp>

class icontrollable {
public:
	virtual ~icontrollable() {}

	virtual void set_movement(int in_val) = 0;
	virtual void launch() = 0;

	bool upper_block = false;
	bool lower_block = false;
};

class object {
public:
	virtual ~object() {}

	virtual void draw(sf::RenderWindow &in_window) = 0;
	virtual void update(float delta_time) = 0;

	virtual bool intersect(object *in_obj) = 0;
	virtual void on_set_position() = 0;


	unsigned int m_global_idx;

	sf::Vector2f m_position;

};
