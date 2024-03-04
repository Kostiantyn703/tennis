#pragma once

#include <SFML/Graphics.hpp>

#include "player.h"

class controller {
public:
	controller();
	~controller();

	player *m_owner = nullptr;

	bool handle_input(sf::RenderWindow &in_window);
};
