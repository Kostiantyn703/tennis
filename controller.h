#pragma once

#include <SFML/Graphics.hpp>

#include "player.h"
#include "interfaces.h"

enum input_event {
	ie_up		= -1,
	ie_down		= 1,
	ie_launch	= 2,
	ie_none		= 0
};

class input_receiver {
public:
	input_event receive_input(sf::RenderWindow &in_window);

	input_event m_last_event = ie_none;
};

class icontroller {
public:
	virtual ~icontroller() {}

	virtual void process_input(input_event in_event);

	void set_owner(icontrollable &in_obj) { m_owner = &in_obj; }

protected:
	virtual void move_up() = 0;
	virtual void move_down() = 0;
	virtual void launch_ball() = 0;
	virtual void stop_movement() = 0;

	icontrollable *m_owner = nullptr;
};

class controller : public icontroller {
public:
	controller() {}
	virtual ~controller() {}

protected:
	virtual void move_up() override;
	virtual void move_down() override;
	virtual void launch_ball() override;
	virtual void stop_movement() override;
	
};
