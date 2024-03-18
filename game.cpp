#pragma warning(disable : 4996)
#include "game.h"
#include "defs.h"
#include <iostream>
#include <stdlib.h>

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	if (!m_font.loadFromFile(FONT_PATH)) {
		std::cout << "Failed to load font." << std::endl;
	}

	m_controller = std::make_unique<controller>();
	
	m_court = std::make_unique<court>();
	m_court->init();
	m_court->init_player(*m_controller.get());
}

void game::init(const network_config &in_config) {
	std::string server("server");
	std::string client("client");
	if (!in_config.m_role.compare(server)) {
		std::cout << "I Am Server" << std::endl;
		m_socket.bind(in_config.m_port);
		std::cout << in_config.m_address << " " << in_config.m_port << std::endl;
	}
	if (!in_config.m_role.compare(client)) {
		std::string message("Client is here");
		std::cout << in_config.m_address << " " << in_config.m_port << std::endl;
		m_socket.bind(51001);
		m_socket.send(message.c_str(), message.size() + 1, in_config.m_address, in_config.m_port);
	}
}

void game::run() {
	float last_time = 0.f;
	while (m_window.isOpen()) {
		float cur_time = m_clock.getElapsedTime().asSeconds();
		float delta_time = cur_time - last_time;
		last_time = cur_time;

		m_controller->handle_input(m_window);
		m_court->update(delta_time);
		render();
		// TODO: test
		/*char buffer[1024];
		size_t received;
		sf::IpAddress addr;
		unsigned short port = 51001;
		if (m_socket.receive(buffer, sizeof(buffer), received, addr, port) == sf::Socket::Status::Done) {
			std::string mess(buffer);
			std::cout << mess << std::endl;
		}*/
	}
}

void game::render() {
	m_window.clear();
	objects objs = m_court->get_objects();
	for (objects::iterator it = objs.begin(); it != objs.end(); ++it) {
		(*it)->draw(m_window);
	}
	// draw net
	sf::RectangleShape net(sf::Vector2f(2.f, WINDOW_HEIGHT));
	net.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 1.f, 0.f));
	m_window.draw(net);

	draw_score(m_court->get_score().player_one, true);
	draw_score(m_court->get_score().player_two, false);

	m_window.display();
}

void game::draw_score(int in_score, bool is_first_player) {
	char buff[3];
	itoa(in_score, buff, 10);
	sf::Text text_score(buff, m_font);
	text_score.setCharacterSize(32);
	text_score.setStyle(sf::Text::Regular);
	if (is_first_player) {
		text_score.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.25f - 16.f, 20.f));
	} else {
		text_score.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.75f - 16.f, 20.f));
	}
	m_window.draw(text_score);
}
