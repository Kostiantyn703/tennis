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

	sf::RenderWindow m_window;

	sf::Clock m_clock;

	std::unique_ptr<input_receiver> m_input;
};

class game_instance {
public: 
	virtual ~game_instance() {}

	virtual void init();

	virtual void update(network &in_network, float delta_time) = 0;
	virtual void handle_input(network &in_network, input_event in_input) = 0;

	void render(sf::RenderWindow &in_window);

protected:
	std::unique_ptr<court> m_court;
	std::unique_ptr<icontroller> m_controller;

	size_t m_frame_count = 0;
	size_t m_frame_divider = 4;

private:
	void draw_score(sf::Text &out_score, int in_score, bool is_first_player);

	sf::Font m_font;
};


class server : public game_instance {
public: 
	server() {}
	virtual ~server() {}

	virtual void init() override;

	virtual void update(network &in_network, float delta_time) override;
	virtual void handle_input(network &in_network, input_event in_input) override;

	void on_score_change(network &in_network);
};

class client : public game_instance {
public:
	client() {}
	virtual ~client() {}

	virtual void init() override;

	virtual void update(network &in_network, float delta_time) override;
	virtual void handle_input(network &in_network, input_event in_input) override;
};
