#pragma once

#include <SFML/Graphics.hpp>

class idrawable {
public:
	virtual ~idrawable() {}

	virtual void draw(sf::RenderWindow &in_window) = 0;
};

class iupdatable {
public:
	virtual ~iupdatable() {}

	virtual void update(float delta_time) = 0;
};

class icontrollable {
public:
	virtual ~icontrollable() {}

	virtual void set_movement(int in_val) = 0;

};

class object : public idrawable, public iupdatable {
public:
	virtual ~object() {}

	virtual void draw(sf::RenderWindow &in_window) override {}
	virtual void update(float delta_time) override {}

	void				set_position	(const sf::Vector2f &in_pos)	{ m_position = in_pos; }
	const sf::Vector2f	&get_position	()	const	{ return m_position; }

protected:
	sf::Vector2f m_position;
};
