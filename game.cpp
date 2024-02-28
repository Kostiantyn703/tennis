#include "game.h"

#include <iostream>

constexpr float WINDOW_HEIGHT = 600;
constexpr float WINDOW_WIDTH = 800;
const char *TITLE = "TENNIS";

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
	std::cout << "Game created.\n";
}

game::~game() {
	std::cout << "Game closed\n";
}

void game::run() {
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		m_window.display();
	}
}
