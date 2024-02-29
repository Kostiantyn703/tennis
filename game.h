#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "controller.h"
#include "player.h"

class game {
	using players = std::vector<player>;
public:
	game();
	~game();

	void run();

private:
	sf::RenderWindow m_window;
	std::unique_ptr<controller> m_controller;
	players m_players;
};
