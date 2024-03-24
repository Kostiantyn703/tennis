#include "network.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "court.h"

static const char *NETWORK_CONFIG_FILENAME = "network.ini";
static const std::string SERVER_STR = "server";
static const std::string CLIENT_STR = "client";

network::network() {
	std::string role_str;
	parse_role(role_str);
	set_role(role_str);
	configure();
}

void network::send_data(sf::Packet &in_packet, std::string &in_data_token) {
	if (m_config.m_role == network_role::nr_server) {
		//m_socket.send(in_packet, m_config.m_address, m_config.m_client_port);
		std::cout << "Score send\n";
	}
}

void network::receive_data(std::string &in_data_token) {
	/*if (m_config.m_role != network_role::nr_client) {
		return;
	}
	sf::Packet packet;
	sf::IpAddress addr;
	unsigned short port = 0;
	if (m_socket.receive(packet, addr, port) == sf::Socket::Status::Done) {
		score_board cur_score;
		sf::Uint16 one;
		sf::Uint16 two;
		packet >> one >> two;

		cur_score.player_one = one;
		cur_score.player_two = two;

		in_court.set_score(cur_score);
		std::cout << "Received score\n";
	}*/
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

	for (std::vector<socket>::iterator it = m_config.m_sockets.begin(); it != m_config.m_sockets.end(); ++it) {
		it->bind();
	}
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
	m_config.m_sockets.push_back(socket(OBJECTS_PORT, OBJECTS_TOKEN));
	m_config.m_sockets.push_back(socket(SCORE_PORT, SCORE_TOKEN));
}

void network::init_client() {
	m_config.m_sockets.push_back(socket(CLIENT_PORT, CLIENT_TOKEN));
}
