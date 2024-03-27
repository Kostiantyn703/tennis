#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>

#include "controller.h"
#include "court.h"
#include "network.h"

class game_instance;

class game {
public:
	game();
	~game() {}

	void run();

private:
	std::unique_ptr<network> m_network;

	std::unique_ptr<game_instance> m_game_impl;
	std::unique_ptr<controller> m_controller;

	sf::RenderWindow m_window;

	sf::Clock m_clock;
};

class game_instance {
public: 
	virtual ~game_instance() {}

	void init(controller &in_controller);

	virtual void update(network &in_network, float delta_time) = 0;

	void render(sf::RenderWindow &in_window);

protected:
	std::unique_ptr<court> m_court;

private:
	void draw_score(sf::Text &out_score, int in_score, bool is_first_player);

	sf::Font m_font;
};


class server : public game_instance {
public: 
	server() {}
	virtual ~server() {}

	virtual void update(network &in_network, float delta_time) override;
	
	void on_score_change(network &in_network);

	float m_network_delay = 0.0045f;
	float m_network_time = 0.f;
};

class client : public game_instance {
public:
	client() {}
	virtual ~client() {}

	virtual void update(network &in_network, float delta_time) override;

};
