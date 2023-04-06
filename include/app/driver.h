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
	
	driver(video::window&, const input::input&, int, int);
	void					step();
	void					sync_display();
	bool					is_exit() const;

	private:

	enum class modes{move_and_draw, color_selection};
	void					sync_canvas_display();
	void					sync_drawer_display();
	void					sync_statusbar_display();
	void					cycle_color(int&, int);
	void					step_move_and_draw();
	void					step_color_selection();

	app::canvas				canvas;
	video::window&			window;
	const input::input&		input;
	app::cursor				cursor;
	
	modes					mode{modes::move_and_draw};
	int						bgcolor{app::colors::white},
							fgcolor{app::colors::white},
							shape{app::types::nothing};
	int						drawer_width,
							status_bar_height;
};
}
