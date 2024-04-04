#pragma warning(disable : 4996)
#include "game.h"
#include "defs.h"
#include <iostream>
#include <stdlib.h>

game::game() {
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE, sf::Style::Titlebar | sf::Style::Close);
	m_network = std::make_unique<network>();
	m_input = std::make_unique<input_receiver>();
	if (m_network->get_role() == network_role::nr_server) {
		std::string final_title(TITLE);
		final_title.append(SERVER_STR);
		m_window.setTitle(final_title);

		m_game_impl = std::make_unique<server>();
		m_game_impl->init();
	}
	if (m_network->get_role() == network_role::nr_client) {
		std::string final_title(TITLE);
		final_title.append(CLIENT_STR);
		m_window.setTitle(final_title);

		m_game_impl = std::make_unique<client>();
		m_game_impl->init();
	}
}

void game::run() {
	float last_time = 0.f;
	while (m_window.isOpen()) {
		float cur_time = m_clock.getElapsedTime().asSeconds();
		float delta_time = cur_time - last_time;
		last_time = cur_time;

		input_event cur_event = m_input->receive_input(m_window);
		m_game_impl->handle_input(*m_network.get(), cur_event);
		m_game_impl->update(*m_network.get(), delta_time);
		m_game_impl->render(m_window);
	}
}

void game_instance::init() {
	if (!m_font.loadFromFile(FONT_PATH)) {
		std::cout << "Failed to load font." << std::endl;
	}
	m_controller = std::make_unique<controller>();
	m_court = std::make_unique<court>();
	m_court->init();
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

void server::init() {
	game_instance::init();
	m_court->p_player_one = m_court->create_player(*m_controller.get(), 0);
	m_court->p_player_two = m_court->create_player(1);
}

void server::update(network &in_network, float delta_time) {
	m_court->update(delta_time);
	if (m_court->check_ball_position()) {
		on_score_change(in_network);
	}
	m_court->p_player_two->set_movement(0);

	if (m_frame_count % m_frame_divider == 0) {
		sf::Packet obj_pack;
		for (objects::const_iterator it = m_court->get_objects().begin(); it != m_court->get_objects().end(); ++it) {
			if ((*it)->m_global_idx == std::numeric_limits<unsigned int>::max()) continue;
			if (!(*it)->is_moving) continue;
			obj_pack << (*it)->m_global_idx << (*it)->m_position.x << (*it)->m_position.y;
			in_network.send_data(obj_pack, OBJECTS_TOKEN);
			obj_pack.clear();
		}
	}
	m_frame_count++;
}

void server::handle_input(network &in_network, input_event in_input) {
	m_controller->process_input(in_input);
	in_network.receive_input(*m_court.get());
}

void server::on_score_change(network &in_network) {
	sf::Packet packet;
	score_board cur_score = m_court->get_score();
	packet << cur_score.player_one << cur_score.player_two;

	in_network.send_data(packet, SCORE_TOKEN);

	m_court->restart();
}

void client::init() {
	game_instance::init();

	m_court->create_player(0);
	m_court->create_player(1); // *m_controller.get(), 
}

void client::update(network &in_network, float delta_time) {
	in_network.receive_data(*m_court);
	in_network.receive_score(*m_court);

	m_frame_count++;
}

void client::handle_input(network &in_network, input_event in_input) {
	if (m_frame_count % m_frame_divider != 0) return;
	if (in_input == 0) return;
	sf::Packet pack;
	sf::Int8 data = in_input;
	pack << data;
	in_network.send_data(pack, CLIENT_INPUT_TOKEN);
}
