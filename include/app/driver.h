#pragma once

#include "video/window.h"
#include "input/input.h"
#include "canvas.h"
#include "cursor.h"
#include "colors.h"
#include "shapes.h"

namespace app {

class driver {

	public:
	
	driver(video::window&, const input::input&, int);
	void					step();
	void					sync_display();

	private:

	void					sync_canvas_display();
	void					sync_drawer_display();
	void					cycle_color(int&, int);

	app::canvas				canvas;
	video::window&			window;
	const input::input&		input;
	app::cursor				cursor;
	
	int						bgcolor{app::colors::white},
							fgcolor{app::colors::white},
							shape{app::types::nothing};
	int						drawer_width;
};
}
