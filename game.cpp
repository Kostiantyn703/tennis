#include "game.h"

#include <iostream>

const char *TITLE = "TENNIS";

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	m_controller = std::make_unique<controller>();
	
	m_players.push_back(player());
}

game::~game() {}

void game::run() {
	//float delta_time = 0.f;
	//float current_time = m_clock.getElapsedTime().asSeconds();
	float last_time = 0.f;
	while (m_window.isOpen()) {
		float cur_time = m_clock.getElapsedTime().asSeconds();
		float delta_time = cur_time - last_time;
		last_time = cur_time;
		//m_clock.restart();
		
		m_controller->handle_input(m_window);
		
		//for (players::iterator it = m_players.begin(); it != m_players.end(); ++it) {
		std::cout << "Delta time: " << delta_time << std::endl;
		m_players.begin()->update(delta_time);
		//delta_time += cur_frame_time;

		m_window.clear();
		m_players.begin()->draw(m_window);
		m_window.display();
	}
}
