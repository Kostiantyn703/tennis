#include "controller.h"

#include <iostream>

controller::controller() {}

controller::~controller() {}

bool controller::handle_input(sf::RenderWindow &in_window) {
	sf::Event cur_event;
	while (in_window.pollEvent(cur_event)) {
		if (cur_event.type == sf::Event::Closed) {
			in_window.close();
		}
		if (!m_owner) break;
		if (cur_event.KeyReleased) {
			m_owner->set_movement(0);
		}
		if (m_owner) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_owner->upper_block) {
				m_owner->set_movement(-1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !m_owner->lower_block) {
				m_owner->set_movement(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				m_owner->launch();
			}
		}
	}
	return false;
}
