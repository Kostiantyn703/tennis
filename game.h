#pragma once

#include <SFML/Graphics.hpp>

class game {
public:
	game();
	~game();

	void run();

private:
	sf::RenderWindow m_window;
};
