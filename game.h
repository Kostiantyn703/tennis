#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include "controller.h"
#include "court.h"

struct network_config {
	std::string m_role;
	unsigned short m_port = 51000;
	std::string m_address = sf::IpAddress::getLocalAddress().toString();
};

class game {
public:
	game();
	~game() {}

	void init(const network_config &in_config);

	void run();

	sf::UdpSocket m_socket;

private:
	void render();
	void draw_score(int in_score, bool is_first_player);

	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Font m_font;

	std::unique_ptr<controller> m_controller;
	std::unique_ptr<court> m_court;
};
