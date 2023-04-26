#include "Main.h"

void Main::run()
{
	initgraph(1024, 768);
	game.initialize(0);
	renderer.initialize();
	bool closed = false;
	renderer.initialize();
	while (!closed)
	{
		// 0xf6f6f5
		game.update();
		renderer.update_env();
		renderer.draw_map(game.map());
		renderer.draw_ui();
		renderer.draw_overlay();
		_getch();
	}
	closegraph();
}
