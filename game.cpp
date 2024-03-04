#include "game.h"

#include <iostream>

const char *TITLE = "TENNIS";

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	m_controller = std::make_unique<controller>();
	
	sf::Vector2f player_one_pos(50.f, WINDOW_HEIGHT * 0.25f);
	sf::Vector2f player_two_pos(WINDOW_WIDTH - 70.f, WINDOW_HEIGHT * 0.65f);

	m_players.push_back(player(player_one_pos));
	m_players.push_back(player(player_two_pos));

	m_controller->m_owner = &m_players[0];

	sf::Vector2f ball_pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);
	m_ball.set_position(ball_pos);

	float border_offset = 10.f;
	sf::Vector2f border_size(WINDOW_WIDTH, border_offset);
	
	border upper_border;
	upper_border.m_shape.setPosition(0.f, 0.f);
	upper_border.m_shape.setSize(border_size);
	m_borders.push_back(upper_border);

	border lower_border;
	lower_border.m_shape.setPosition(0.f, WINDOW_HEIGHT - border_offset);
	lower_border.m_shape.setSize(border_size);
	m_borders.push_back(lower_border);
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
		if (!is_active) {
			m_ball.set_position(m_players[m_ball.get_player_idx()].get_position());
		}

		m_window.clear();
		for (players::iterator it = m_players.begin(); it != m_players.end(); ++it) {
			it->draw(m_window);
		}
		m_ball.draw(m_window);
		for (std::vector<border>::const_iterator it = m_borders.begin(); it != m_borders.end(); ++it) {
			m_window.draw(it->m_shape);
		}
		m_window.display();
	}
}
