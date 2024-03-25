#pragma warning(disable : 4996)
#include "game.h"
#include "defs.h"
#include <iostream>
#include <stdlib.h>

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	m_network = std::make_unique<network>();
	if (m_network->get_role() == network_role::nr_server) {
		m_game_impl = std::make_unique<server>();
		m_controller = std::make_unique<controller>();
		m_game_impl->init(*m_controller.get());
	}
	if (m_network->get_role() == network_role::nr_client) {
		// TODO: implement client init
	}
}

void game::run() {
	while (m_window.isOpen()) {
		m_controller->handle_input(m_window);
		m_game_impl->update();
		m_game_impl->render(m_window);
	}
}

void game_instance::init(controller &in_controller) {
	if (!m_font.loadFromFile(FONT_PATH)) {
		std::cout << "Failed to load font." << std::endl;
	}

	m_court = std::make_unique<court>();
	m_court->init();
	m_court->init_player(in_controller);
}

void game_instance::on_score_change() {
	/*sf::Packet packet;
	score_board cur_score = m_court->get_score();
	packet << cur_score.player_one << cur_score.player_two;

	m_network.send_data(packet, SCORE_TOKEN); */

	m_court->restart();
}


void game_instance::render(sf::RenderWindow &in_window) {
	in_window.clear();
	objects objs = m_court->get_objects();
	for (objects::iterator it = objs.begin(); it != objs.end(); ++it) {
		(*it)->draw(in_window);
	}
	// draw net
	sf::RectangleShape net(sf::Vector2f(2.f, WINDOW_HEIGHT));
	net.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 1.f, 0.f));
	in_window.draw(net);
	// draw score
	sf::Text score_player_one;
	draw_score(score_player_one, m_court->get_score().player_one, true);
	in_window.draw(score_player_one);
	
	sf::Text score_player_two;
	draw_score(score_player_two, m_court->get_score().player_two, false);
	in_window.draw(score_player_two);

	in_window.display();
}

void game_instance::draw_score(sf::Text &out_score, int in_score, bool is_first_player) {
	char score_buff[8];
	itoa(in_score, score_buff, 10);
	out_score.setFont(m_font);
	out_score.setString(score_buff);
	out_score.setCharacterSize(32);
	out_score.setStyle(sf::Text::Regular);
	if (is_first_player) {
		out_score.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.25f - 16.f, 20.f));
	} else {
		out_score.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.75f - 16.f, 20.f));
	}
}

void server::update() {
	float cur_time = m_clock.getElapsedTime().asSeconds();
	float delta_time = cur_time - last_time;
	last_time = cur_time;
	m_court->update(*this, delta_time);
}

void client::update() {
	/*if (m_network.get_role() != network_role::nr_server) {
		m_network.receive_data(*m_court);
	}*/

}
