#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "controller.h"
#include "player.h"
#include "ball.h"

constexpr size_t WINDOW_HEIGHT = 600;
constexpr size_t WINDOW_WIDTH = 800;

struct border {
	sf::RectangleShape m_shape;
};

class game {
	using players = std::vector<player>;
public:
	game();
	~game();

	void run();

private:
	std::vector<border> m_borders;

	sf::RenderWindow m_window;
	sf::Clock m_clock;

	std::unique_ptr<controller> m_controller;
	players m_players;

	ball m_ball;

	bool is_active = false;
};
