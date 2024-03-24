#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>

// socket data
const std::string OBJECTS_TOKEN	= "objects";
const std::string SCORE_TOKEN	= "score";
const std::string CLIENT_TOKEN	= "client";

constexpr unsigned short OBJECTS_PORT	= 51000;
constexpr unsigned short SCORE_PORT		= 51001;
constexpr unsigned short CLIENT_PORT	= 51002;

class court;

enum class network_role {
	nr_server,
	nr_client,
	nr_none
};

class socket {
public:
	socket(const unsigned short in_port, const std::string &in_name) {
		m_port = in_port;
		m_name = in_name;
	}

	socket(const socket &rhs) {
		m_port = rhs.m_port;
		m_name = rhs.m_name;
	}

	void bind() {
		m_socket.bind(m_port);
		m_socket.setBlocking(false);
	}

	unsigned short m_port;
	std::string m_name;
	sf::UdpSocket m_socket;
};

struct network_config {
	network_role m_role = network_role::nr_server;

	sf::IpAddress m_address = sf::IpAddress::getLocalAddress();

	std::vector<socket> m_sockets;
};

class network {
public:
	network();
	~network() {}

	void send_data(sf::Packet &in_packet, std::string &in_data_token);
	void receive_data(std::string &in_data_token);

	void configure();
	
private:
	network_config m_config;

	void parse_role(std::string &out_result);
	void set_role(const std::string &in_role);

	void init_server();
	void init_client();
};
