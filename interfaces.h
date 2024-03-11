#pragma once

#include <SFML/Graphics.hpp>

enum object_type {
	OT_BORDER,
	OT_BALL,
	OT_PADDLE,
	OT_NONE
};

class icontrollable {
public:
	virtual ~icontrollable() {}

	virtual void set_movement(int in_val) = 0;
};

class object {
public:
	virtual ~object() {}

	virtual void draw(sf::RenderWindow &in_window) = 0;
	virtual void update(float delta_time) = 0;

	virtual void intersect(object &in_obj) = 0;
	virtual void on_intersect() = 0;
protected:
	object_type m_type; 
};
