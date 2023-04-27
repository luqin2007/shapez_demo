#include "Main.h"

#include <iostream>

void Main::run()
{
	initgraph(1024, 768);
	game_.initialize(0);
	renderer_.initialize();
	while (hiex::IsAnyWindow())
	{
		// game_.update();
		BEGIN_TASK();
		renderer_.update_env();
		renderer_.draw_map(game_.map());
		renderer_.draw_building(game_.map());
		renderer_.draw_ui();
		renderer_.draw_overlay();
		END_TASK();
		REDRAW_WINDOW();
	}
	closegraph();
}
