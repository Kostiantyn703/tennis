#pragma once

#include <SFML/Graphics.hpp>

#include "player.h"
#include "interfaces.h"

enum input_event {
	ie_up,
	ie_down,
	ie_launch,
	ie_none
};

class input_receiver {
public:
	input_event receive_input(sf::RenderWindow &in_window);

	input_event m_last_event = ie_none;
};

class icontroller {
public:
	virtual ~icontroller() {}

	virtual void move_up() = 0;
	virtual void move_down() = 0;
	virtual void launch_ball() = 0;
	virtual void stop_movement() = 0;

	virtual void set_owner(icontrollable &in_obj) = 0;

	virtual void process_input(input_event in_event);
};

class controller : public icontroller {
public:
	controller() {}
	virtual ~controller() {}

	virtual void set_owner(icontrollable &in_obj) override { m_owner = &in_obj; }

	virtual void move_up() override;
	virtual void move_down() override;
	virtual void launch_ball() override;
	virtual void stop_movement() override;
private:
	icontrollable *m_owner = nullptr;
};
