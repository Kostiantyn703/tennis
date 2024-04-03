#include "controller.h"

#include <iostream>

input_event input_receiver::receive_input(sf::RenderWindow &in_window) {
	sf::Event cur_event;
	while (in_window.pollEvent(cur_event)) {
		if (cur_event.type == sf::Event::Closed) {
			in_window.close();
			m_last_event = input_event::ie_none;
		}
		if (m_last_event != input_event::ie_none && cur_event.KeyReleased) {
			m_last_event = input_event::ie_none;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_last_event = input_event::ie_up;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_last_event = input_event::ie_down;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			m_last_event =  input_event::ie_launch;
		}
	}
	return m_last_event;
}


void icontroller::process_input(input_event in_event) {
	switch (in_event) {
	case input_event::ie_up:
		move_up();
		break;
	case input_event::ie_down:
		move_down();
		break;
	case input_event::ie_launch:
		launch_ball();
		break;
	case input_event::ie_none:
	default:
		stop_movement();
	}
}

void controller::move_up() {
	if (!m_owner->upper_block) {
		m_owner->set_movement(-1);
	}
}

void controller::move_down() {
	if (!m_owner->lower_block) {
		m_owner->set_movement(1);
	}
}

void controller::launch_ball() {
	if (m_owner->m_ball_slot) {
		m_owner->launch();
	}
}

void controller::stop_movement() {
	m_owner->set_movement(0);
}