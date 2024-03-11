#pragma once

#include <SFML/Graphics.hpp>

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
};
