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
	float delta_time = 0.01f;
	while (m_window.isOpen()) {
		m_controller->handle_input(m_window);
		m_window.clear();
		for (players::iterator it = m_players.begin(); it != m_players.end(); ++it) {
			it->update(delta_time);
			it->draw(m_window);
		}
		m_window.display();
	}
}
