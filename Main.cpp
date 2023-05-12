#include "Main.h"

void Main::run()
{
	window_.initialize();
	game_.initialize(0);
	renderer_.initialize();
	while (window_.is_active())
	{
		game_.update();
		renderer_.update_env(game_.map());
		renderer_.draw(game_.map());
		glfwSwapBuffers(window_.window());
		glfwPollEvents();
	}

	renderer_.destroy();
	window_.destroy();
}
