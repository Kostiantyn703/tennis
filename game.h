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
	std::unique_ptr<input_receiver> m_input;

	sf::RenderWindow m_window;
	sf::Clock m_clock;

	void set_name(const std::string &in_string);
};

class game_instance {
	using controllers = std::vector<std::unique_ptr<icontroller>>;
public: 
	virtual ~game_instance() {}

	virtual void update(network &in_network, float delta_time) = 0;
	virtual void handle_input(network &in_network, input_event in_input) = 0;

	void render(sf::RenderWindow &in_window);

protected:
	std::unique_ptr<court> m_court;
	controllers m_controllers;

	size_t m_frame_count = 0;
	size_t m_frame_module = 4;

	virtual void init();
private:
	void draw_score(sf::Text &out_score, int in_score, bool is_first_player);

	sf::Font m_font;
};

class server : public game_instance {
public: 
	server() { init(); }
	virtual ~server() {}

	virtual void update(network &in_network, float delta_time) override;
	virtual void handle_input(network &in_network, input_event in_input) override;

	void on_score_change(network &in_network);

protected:
	virtual void init() override;
};

class client : public game_instance {
public:
	client() { init(); }
	virtual ~client() {}

	virtual void update(network &in_network, float delta_time) override;
	virtual void handle_input(network &in_network, input_event in_input) override;

protected:
	virtual void init() override;
};
