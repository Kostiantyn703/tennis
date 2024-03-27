#include "court.h"

#include <limits>

#include "controller.h"
#include "defs.h"
#include "game.h"


border::border(const sf::Vector2f & in_pos, const sf::Vector2f &in_size) {
	m_shape.setPosition(in_pos);
	m_shape.setSize(in_size);

	m_global_idx = std::numeric_limits<unsigned int>::max();
}

void border::draw(sf::RenderWindow &in_window) {
	in_window.draw(m_shape);
}

court::court() {
	m_players_pos.push_back(sf::Vector2f(50.f, WINDOW_HEIGHT * 0.25f));
	m_players_pos.push_back(sf::Vector2f(WINDOW_WIDTH - 60.f, WINDOW_HEIGHT * 0.25f));
	//m_players_pos.push_back(sf::Vector2f(WINDOW_WIDTH - 60.f, WINDOW_HEIGHT * 0.65f));
}

court::~court() {
	for (objects::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		delete *it;
	}
	m_objects.clear();
}

void court::init() {
	sf::Vector2f border_size(WINDOW_WIDTH, BORDER_OFFSET);

	border *upper_border = new border(sf::Vector2f(0.f, 0.f), border_size);
	m_objects.push_back(upper_border);

	border *lower_border = new border(sf::Vector2f(0.f, WINDOW_HEIGHT - BORDER_OFFSET), border_size);
	m_objects.push_back(lower_border);
}

void court::init_player(controller &out_controller) {
	player *cur_player = new player(m_players_pos[0]);
	cur_player->set_idx(0);
	m_player_one = cur_player;

	sf::Vector2f ball_pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);
	ball *cur_ball = new ball;
	cur_ball->set_position(ball_pos);
	cur_ball->m_global_idx = (unsigned int)m_objects.size();
	m_objects.push_back(cur_ball);

	m_ball_slot = cur_ball;
	cur_player->m_ball_slot = cur_ball;

	out_controller.set_owner(*cur_player);

	cur_player->m_global_idx = (unsigned int)m_objects.size();
	m_objects.push_back(cur_player);

}

void court::update(float delta_time) {
	for (objects::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		(*it)->update(delta_time);
		for (objects::iterator local_it = m_objects.begin(); local_it != m_objects.end(); ++local_it) {
			if ((*it)->intersect(*local_it)) {
				break;
			}
		}
	}
}

bool court::check_ball_position() {
	bool result = false;
	float ball_pos = m_ball_slot->get_shape().getPosition().x;
	if (ball_pos < 0.f) {
		m_score.player_two++;
		result = true;
	}
	if (m_ball_slot->get_shape().getPosition().x > WINDOW_WIDTH) {
		m_score.player_one++;
		result = true;
	}
	return result;
}

void court::restart() {
	for (objects::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		if (ball *cur_ball = dynamic_cast<ball*>(*it)) {
			cur_ball->set_position(m_player_one->get_position());
			cur_ball->is_sticked = true;
			m_player_one->m_ball_slot = cur_ball;
			continue;
		}
	}
}
