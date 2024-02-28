#include "game.h"

#include <iostream>

constexpr size_t WINDOW_HEIGHT = 600;
constexpr size_t WINDOW_WIDTH = 800;
const char *TITLE = "TENNIS";

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	m_controller = std::make_unique<controller>();
}

game::~game() {
}

void game::run() {
	while (m_window.isOpen())
	{
		m_controller->handle_input(m_window);
		
		m_window.display();
	}
}
