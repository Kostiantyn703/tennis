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

	void on_score_change();

private:
	std::unique_ptr<network> m_network;

	std::unique_ptr<game_instance> m_game_impl;
	std::unique_ptr<controller> m_controller;

	void draw_score(int in_score, bool is_first_player);

	sf::RenderWindow m_window;

	sf::Font m_font;

};

class game_instance {
public: 
	virtual ~game_instance() {}

	virtual void update() = 0;

	void init(controller &in_controller);

	void render(sf::RenderWindow &in_window);

protected:

	std::unique_ptr<court> m_court;
};


class server : public game_instance {
public: 
	server() {}
	virtual ~server() {}

	virtual void update() override;

private:
	float last_time = 0.f;
	sf::Clock m_clock;
};

class client : public game_instance {
public:
	client() {}
	virtual ~client() {}

	virtual void update() override;
};
