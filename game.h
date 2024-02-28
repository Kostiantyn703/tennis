#pragma once

#include <SFML/Graphics.hpp>

#include "controller.h"

class game {
public:
	game();
	~game();

	void run();

private:
	sf::RenderWindow m_window;
	std::unique_ptr<controller> m_controller;
};
