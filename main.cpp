#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "game.h"

void parse_network_role(std::string &out_result);

int main() {
	network_config config;
	parse_network_role(config.m_role);
	std::unique_ptr<game> application = std::make_unique<game>();
	application->init(config);
	application->run();
	return 0;
}

void parse_network_role(std::string &out_result) {
	std::ifstream read_stream(NETWORK_CONFIG_FILENAME);
	if (!read_stream.is_open()) {
		std::cout << "Failed to load network config.\n";
		return;
	}

	std::stringstream str_stream;
	str_stream << read_stream.rdbuf();
	out_result = str_stream.str();
}
