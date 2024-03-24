#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>

#include "controller.h"
#include "court.h"
#include "network.h"

class game {
public:
	game();
	~game() {}

	void init();

	void run();

private:
	void render();
	void draw_score(int in_score, bool is_first_player);

	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Font m_font;

	std::unique_ptr<controller> m_controller;
	std::unique_ptr<court> m_court;
	
	network m_network;
};
