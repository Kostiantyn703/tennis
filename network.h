#pragma once

#include <string>
#include <SFML/Network.hpp>

enum class network_role {
	nr_server,
	nr_client,
	nr_none
};

struct network_config {
	network_role m_role = network_role::nr_server;
	unsigned short m_port = 51000;
	std::string m_address = sf::IpAddress::getLocalAddress().toString();
};

class network {
	static network *instance;
public:
	~network() {}

	static network *get_instance() {
		if (!instance) {
			instance = new network();
		}
		return instance;
	}
	void connect();

	void send_data(sf::Packet &in_packet);
	void receive_data();

	network_config m_config;
	sf::UdpSocket m_socket;
private:
	network();

	void parse_role(std::string &out_result);
	void configure();
	void set_role(const std::string &in_role);

};
