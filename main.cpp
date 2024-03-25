#include <memory>
#include "game.h"

int main() {
	std::unique_ptr<game> application = std::make_unique<game>();
	application->run();
	return 0;
}
