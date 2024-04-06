#include "network.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "court.h"

static const char *NETWORK_CONFIG_FILENAME = "network.ini";

network::network() {
	std::string role_str;
	parse_role(role_str);
	set_role(role_str);
	configure();
}

void network::send_data(sf::Packet &in_packet, const std::string in_data_token) {
	if (!in_data_token.compare(SCORE_TOKEN)) {
		m_config.m_score_socket.send(in_packet, m_config.m_address, CLIENT_SCORE_PORT);
	}
	if (!in_data_token.compare(OBJECTS_TOKEN)) {
		m_config.m_objects_socket.send(in_packet, m_config.m_address, CLIENT_OBJECTS_PORT);
	}
	if (!in_data_token.compare(CLIENT_INPUT_TOKEN)) {
		m_config.m_input_socket.send(in_packet, m_config.m_address, SERVER_INPUT_PORT);
	}
}

void network::receive_data(court &in_court) {
	sf::Packet packet;
	sf::IpAddress addr;
	unsigned short port = 0;
	if (m_config.m_objects_socket.receive(packet, addr, port) == sf::Socket::Status::Done) {
		float coord_x = 0.f;
		float coord_y = 0.f;
		unsigned int idx = 0;
		if (packet >> idx >> coord_x >> coord_y) {
			auto search_pred = [&idx](object *obj) {
				return obj->m_global_idx == idx;
			};
			auto it = std::find_if(in_court.get_objects().begin(), in_court.get_objects().end(), search_pred);
			if (it != in_court.get_objects().end()) {
				sf::Vector2f cur_pos(coord_x, coord_y);
				(*it)->m_position = cur_pos;
				(*it)->on_set_position();
			}
		}
	}
	packet.clear();
}

void network::receive_score(court &in_court) {
	sf::Packet packet;
	sf::IpAddress addr;
	unsigned short port = 0;
	if (m_config.m_score_socket.receive(packet, addr, port) == sf::Socket::Status::Done) {
		score_board cur_score;
		sf::Uint16 one;
		sf::Uint16 two;
		packet >> one >> two;

		cur_score.player_one = one;
		cur_score.player_two = two;

		in_court.set_score(cur_score);
	}
	packet.clear();
}

int network::receive_input(court &in_court) {
	sf::Packet packet;
	sf::IpAddress addr;
	unsigned short port = 0;
	if (m_config.m_input_socket.receive(packet, addr, port) == sf::Socket::Status::Done) {
		sf::Int8 data;
		packet >> data;
		packet.clear();
		return (int)data;
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
		init_server();
		break;
	case network_role::nr_client:
		init_client();
		break;
	default:
		std::cout << "Network wasn't properly initialized.\n";
	}
	m_config.m_score_socket.setBlocking(false);
	m_config.m_objects_socket.setBlocking(false);
	m_config.m_input_socket.setBlocking(false);
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

void network::init_server() {
	m_config.m_score_socket.bind(SERVER_SCORE_PORT);
	m_config.m_objects_socket.bind(SERVER_OBJECTS_PORT);
	m_config.m_input_socket.bind(SERVER_INPUT_PORT);
	m_config.m_connect_listener.listen(CONNECTION_PORT);
	if (m_config.m_connect_listener.accept(m_config.m_connect_socket) == sf::Socket::Done) {
		std::cout << "Client connected\n";
	}
}

void network::init_client() {
	m_config.m_score_socket.bind(CLIENT_SCORE_PORT);
	m_config.m_objects_socket.bind(CLIENT_OBJECTS_PORT);
	m_config.m_input_socket.bind(CLIENT_INPUT_PORT);
	if (m_config.m_connect_socket.connect(m_config.m_address, CONNECTION_PORT) == sf::Socket::Done) {
		std::cout << "Connected to server.\n";
	}
}
