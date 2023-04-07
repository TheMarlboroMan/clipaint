#pragma once

#include "video/window.h"
#include "input/input.h"
#include "canvas.h"
#include "cursor.h"
#include "colors.h"
#include <string>

namespace app {

class driver {

	public:
	
	driver(video::window&, const input::input&, int, int);
	void					step(double);
	void					sync_display();
	bool					is_exit() const;

	private:

	enum class modes{move_and_draw, color_selection};
	void					sync_canvas_display();
	void					sync_drawer_display();
	void					sync_statusbar_display();
	void					sync_cursor_position();
	void					cycle_color(int&, int);
	void					step_move_and_draw(double);
	void					step_color_selection(double);
	void					build_message(const std::string&);

	app::canvas				canvas;
	video::window&			window;
	const input::input&		input;
	app::cursor				cursor;
	
	modes					mode{modes::move_and_draw};
	int						bgcolor{app::colors::white},
							fgcolor{app::colors::white};
	char					shape{' '};
	int						drawer_width,
							status_bar_height;
	std::string				message;
	double					cursor_blink_timer{0.0};

	const double			cursor_blink_cycle_len{0.6};
};
}
