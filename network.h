#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>


// socket data
static const std::string SERVER_STR = "server";
static const std::string CLIENT_STR = "client";

static const std::string OBJECTS_TOKEN = "objects";
static const std::string SCORE_TOKEN = "score";
static const std::string CLIENT_INPUT_TOKEN = "client_input";

constexpr unsigned short CONNECTION_PORT = 50000;

constexpr unsigned short SERVER_SCORE_PORT = 51001;
constexpr unsigned short SERVER_OBJECTS_PORT = 51002;
constexpr unsigned short SERVER_INPUT_PORT = 51003;

constexpr unsigned short CLIENT_SCORE_PORT = 51004;
constexpr unsigned short CLIENT_OBJECTS_PORT = 51005;
constexpr unsigned short CLIENT_INPUT_PORT = 51006;

class court;

enum class network_role {
	nr_server,
	nr_client,
	nr_none
};

struct network_config {
	network_role m_role = network_role::nr_server;

	sf::IpAddress m_address = sf::IpAddress::getLocalAddress();

	sf::UdpSocket m_score_socket;
	sf::UdpSocket m_objects_socket;
	sf::UdpSocket m_input_socket;

	// for connection
	sf::TcpListener m_connect_listener;
	sf::TcpSocket m_connect_socket;
};

class network {
public:
	network();
	~network() {}

	void send_data(sf::Packet &in_packet, const std::string in_data_token);
	void receive_data(court &in_court);
	void receive_score(court &in_court);
	int receive_input(court &in_court);

	network_role get_role() const { return m_config.m_role; }

private:
	network_config m_config;

	void configure();

	void parse_role(std::string &out_result);
	void set_role(const std::string &in_role);

	void init_server();
	void init_client();
};
