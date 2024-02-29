#include "game.h"

#include <iostream>

constexpr size_t WINDOW_HEIGHT = 600;
constexpr size_t WINDOW_WIDTH = 800;
const char *TITLE = "TENNIS";

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	m_controller = std::make_unique<controller>();
	
	m_players.push_back(player());
}

game::~game() {}

void game::run() {
	while (m_window.isOpen()) {
		m_controller->handle_input(m_window);
		for (players::iterator it = m_players.begin(); it != m_players.end(); ++it) {
			m_window.draw(it->get_shape());
		}
		m_window.display();
	}
}
