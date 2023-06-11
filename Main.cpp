#include "Main.h"

void Main::run()
{
	// 初始化
	window_.initialize();
	game_.initialize(Timer::time());
	renderer_.initialize();
	// 游戏循环
	while (window_.is_alive())
	{
		game_.update();
		renderer_.update(game_);
		glfwSwapBuffers(window_.window());
		glfwPollEvents();
	}
	// 结束
	renderer_.destroy();
	game_.destroy();
	window_.destroy();
}
