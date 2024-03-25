#pragma warning(disable : 4996)
#include "game.h"
#include "defs.h"
#include <iostream>
#include <stdlib.h>

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	if (!m_font.loadFromFile(FONT_PATH)) {
		std::cout << "Failed to load font." << std::endl;
	}

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

void game::draw_score(int in_score, bool is_first_player) {
	char score_buff[8];
	itoa(in_score, score_buff, 10);
	sf::Text text_score(score_buff, m_font);
	text_score.setCharacterSize(32);
	text_score.setStyle(sf::Text::Regular);
	if (is_first_player) {
		text_score.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.25f - 16.f, 20.f));
	} else {
		text_score.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.75f - 16.f, 20.f));
	}
	m_window.draw(text_score);
}

void game::on_score_change() {
	/*sf::Packet packet;
	score_board cur_score = m_court->get_score();
	packet << cur_score.player_one << cur_score.player_two;

	m_network.send_data(packet, SCORE_TOKEN);

	m_court->restart();*/
}

void game_instance::init(controller &in_controller) {
	m_court = std::make_unique<court>();
	m_court->init();
	m_court->init_player(in_controller);
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

	//draw_score(m_court->get_score().player_one, true);
	//draw_score(m_court->get_score().player_two, false);

	in_window.display();
}

void server::update() {
	float cur_time = m_clock.getElapsedTime().asSeconds();
	float delta_time = cur_time - last_time;
	last_time = cur_time;
	m_court->update(delta_time);

}

void client::update() {
	/*if (m_network.get_role() != network_role::nr_server) {
		m_network.receive_data(*m_court);
	}*/

}
