#include "network.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

static const char *NETWORK_CONFIG_FILENAME = "network.ini";
const std::string SERVER_STR = "server";
const std::string CLIENT_STR = "client";

network *network::instance = nullptr;

network::network() {
	std::string role_str;
	parse_role(role_str);
	set_role(role_str);
	configure();
}

void network::connect() {
	std::string client_message("Client connected.");
	m_socket.send(client_message.c_str(), client_message.size() + 1, m_config.m_address, m_config.m_port);
}

void network::send_data(sf::Packet &in_packet) {
	m_socket.send(in_packet, m_config.m_address, m_config.m_port);
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
		connect();
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

