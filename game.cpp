#include "game.h"
#include <iostream>
#include "defs.h"

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	m_controller = std::make_unique<controller>();
	
	m_court = std::make_unique<court>();
	m_court->init();
	m_court->init_player(*m_controller.get());
}

game::~game() {}

void game::run() {
	float last_time = 0.f;
	while (m_window.isOpen()) {
		float cur_time = m_clock.getElapsedTime().asSeconds();
		float delta_time = cur_time - last_time;
		last_time = cur_time;

		m_controller->handle_input(m_window);
		m_court->update(delta_time);
		render();
	}
}

void game::render() {
	m_window.clear();
	objects objs = m_court->get_objects();
	for (objects::iterator it = objs.begin(); it != objs.end(); ++it) {
		(*it)->draw(m_window);
	}
	m_window.display();
}
