#include "controller.h"

controller::controller() {


}

controller::~controller() {

}

bool controller::handle_input(sf::RenderWindow &in_window) {
	sf::Event cur_event;
	while (in_window.pollEvent(cur_event)) {
		if (cur_event.type == sf::Event::Closed)
			in_window.close();
	}
	return false;
}
