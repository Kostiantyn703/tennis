#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "interfaces.h"
#include "player.h"
#include "ball.h"

using objects = std::vector<object*>;

class game_instance;
class controller;

class border : public object {
public:
	border(const sf::Vector2f &in_pos, const sf::Vector2f &in_size);
	virtual ~border() {}

	virtual void draw(sf::RenderWindow &in_window) override;
	virtual void update(float delta_time) override {}
	virtual void on_set_position() override {}

	virtual bool intersect(object *in_obj) override { return false; }

	const sf::RectangleShape &get_shape() const { return m_shape; }

private:
	sf::RectangleShape m_shape;
};

struct score_board {
	sf::Uint16 player_one = 0;
	sf::Uint16 player_two = 0;
};

class court {
public:
	court();
	~court();

	void init();
	void init_player(controller &out_controller);
	void init_player(); // second player init

	void update(float delta_time);
	bool check_ball_position();

	const objects &get_objects() const { return m_objects; }
	const score_board &get_score() const { return m_score; }

	void set_score(score_board &in_score) { m_score = in_score; }

	void restart();

private:
	objects m_objects;
	score_board m_score;

	player *m_player_one = nullptr;
	player *m_player_two = nullptr;
	ball *m_ball_slot = nullptr;

	size_t m_winner = 0;

	std::vector<sf::Vector2f> m_players_pos;
};
