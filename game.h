#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>

#include "controller.h"
#include "court.h"

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
public:
	network() {}
	~network() {}

	void send_data();
	void receive_data();
	void parse_role(std::string &out_result);
	void configure();
	void set_role(const std::string &in_role);


	network_config m_config;
	sf::UdpSocket m_socket;
};

class game {
public:
	game();
	~game() {}

	void init();

	void run();

private:
	void render();
	void draw_score(int in_score, bool is_first_player);

	std::unique_ptr<network> m_network;

	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Font m_font;

	std::unique_ptr<controller> m_controller;
	std::unique_ptr<court> m_court;
};
