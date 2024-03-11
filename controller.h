#pragma once

#include <SFML/Graphics.hpp>

#include "player.h"
#include "interfaces.h"

class controller {
public:
	controller();
	~controller();

	void set_owner(icontrollable &in_obj) { m_owner = &in_obj; }

	bool handle_input(sf::RenderWindow &in_window);
private:
	icontrollable *m_owner = nullptr;
};
