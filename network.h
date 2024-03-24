#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>

// socket data
static const std::string SERVER_STR = "server";
static const std::string CLIENT_STR = "client";

constexpr unsigned short SERVER_PORT = 51000;
constexpr unsigned short CLIENT_PORT = 51001;

class court;

enum class network_role {
	nr_server,
	nr_client,
	nr_none
};

struct network_config {
	network_role m_role = network_role::nr_server;

	sf::IpAddress m_address = sf::IpAddress::getLocalAddress();

	sf::UdpSocket m_socket;
};

class network {
public:
	network();
	~network() {}

	void send_data(sf::Packet &in_packet);
	void receive_data(court &in_court);

	void configure();
	
private:
	network_config m_config;

	void parse_role(std::string &out_result);
	void set_role(const std::string &in_role);

	void init_server();
	void init_client();
};
