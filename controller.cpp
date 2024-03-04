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
			m_owner->set_direction(0);
			//break;
		}
		if (m_owner) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_owner->set_direction(-1);
				//break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_owner->set_direction(1);
				//break;
			}
		}
	}
	return false;
}
