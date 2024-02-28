#pragma once

#include <SFML/Graphics.hpp>

class controller {
public:
	controller();
	~controller();

	bool handle_input(sf::RenderWindow &in_window);
};
