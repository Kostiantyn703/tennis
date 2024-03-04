#include "game.h"

#include <iostream>

const char *TITLE = "TENNIS";

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	m_controller = std::make_unique<controller>();
	
	sf::Vector2f player_one_pos(50.f, WINDOW_HEIGHT * 0.35f);
	sf::Vector2f player_two_pos(WINDOW_WIDTH - 70.f, WINDOW_HEIGHT * 0.65f);

	m_players.push_back(player(player_one_pos));
	m_players.push_back(player(player_two_pos));

	m_controller->m_owner = &m_players[0];
}

game::~game() {}

void game::run() {
	float last_time = 0.f;
	while (m_window.isOpen()) {
		float cur_time = m_clock.getElapsedTime().asSeconds();
		float delta_time = cur_time - last_time;
		last_time = cur_time;

		m_controller->handle_input(m_window);
		for (players::iterator it = m_players.begin(); it != m_players.end(); ++it) {
			it->update(delta_time);
		}

		m_window.clear();
		for (players::iterator it = m_players.begin(); it != m_players.end(); ++it) {
			it->draw(m_window);
		}
		m_window.display();
	}
}
