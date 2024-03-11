#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "controller.h"
#include "court.h"

class game {

public:
	game();
	~game();

	void run();

private:
	void render();

	sf::RenderWindow m_window;
	sf::Clock m_clock;

	std::unique_ptr<controller> m_controller;

	std::unique_ptr<court> m_court;

	bool is_active = false;
};
