#pragma warning(disable : 4996)
#include "game.h"
#include "defs.h"
#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

const std::string SERVER_STR = "server";
const std::string CLIENT_STR = "client";


void network::send_data() {
	std::string client_message("Client connected.");
	m_socket.send(client_message.c_str(), client_message.size() + 1, m_config.m_address, m_config.m_port);
}

void network::receive_data() {
	char buffer[1024];
	size_t received;
	sf::IpAddress addr;
	if (m_socket.receive(buffer, sizeof(buffer), received, addr, m_config.m_port) == sf::Socket::Status::Done) {
		std::string mess(buffer);
		std::cout << mess << std::endl;
	}
}

void network::parse_role(std::string &out_result) {
	std::ifstream read_stream(NETWORK_CONFIG_FILENAME);
	if (!read_stream.is_open()) {
		std::cout << "Failed to load network config.\n";
		return;
	}

	std::stringstream str_stream;
	str_stream << read_stream.rdbuf();
	out_result = str_stream.str();
}

void network::configure() {
	switch (m_config.m_role) {
		case network_role::nr_server:
			std::cout << "Server initialized" << std::endl;
			m_socket.bind(m_config.m_port);
		break;
		case network_role::nr_client:
			send_data();
		break;
		default:
		std::cout << "Network wasn't properly initialized.\n";
	}
	m_socket.setBlocking(false);
}

void network::set_role(const std::string &in_role) {
	if (!in_role.compare(SERVER_STR)) {
		m_config.m_role = network_role::nr_server;
		return;
	}
	if (!in_role.compare(CLIENT_STR)) {
		m_config.m_role = network_role::nr_client;
		return;
	}
}

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

void game::init() {
	m_network = std::make_unique<network>();

	std::string role_str;
	m_network->parse_role(role_str);
	m_network->set_role(role_str);
	m_network->configure();
}

void game::run() {
	float last_time = 0.f;
	while (m_window.isOpen()) {
		float cur_time = m_clock.getElapsedTime().asSeconds();
		float delta_time = cur_time - last_time;
		last_time = cur_time;

		m_network->receive_data();

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
