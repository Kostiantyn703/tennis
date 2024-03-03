#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "controller.h"
#include "player.h"

constexpr size_t WINDOW_HEIGHT = 600;
constexpr size_t WINDOW_WIDTH = 800;

constexpr size_t FRAMES_PER_SECOND = 30;
constexpr float FRAME_TIME = 1.f / FRAMES_PER_SECOND;


class game {
	using players = std::vector<player>;
public:
	game();
	~game();

	void run();

private:
	sf::RenderWindow m_window;
	sf::Clock m_clock;

	std::unique_ptr<controller> m_controller;
	players m_players;
};
