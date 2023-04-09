#include "app/driver.h"
#include "app/colors.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

using namespace app;

driver::driver(
	video::window& _window,
	const input::input& _input,
	int _drawer_w,
	int _statusbar_h
):
	canvas{_window.get_w()-_drawer_w, _window.get_h()-_statusbar_h},
	window{_window},
	input{_input},
	drawer_width(_drawer_w),
	status_bar_height(_statusbar_h)
{
	sync_display();
	build_message("welcome!");
}

void driver::build_message(
	const std::string& _in
) {

	message=_in.substr(0, window.get_w());
}

void driver::step(
	double _delta
) {

	switch(mode) {

		case modes::move_and_draw:
			step_move_and_draw(_delta);
		break;
		case modes::color_selection:
			step_color_selection(_delta);
		break;
	}
}

bool driver::is_exit() const {

	return mode==modes::move_and_draw && input.is_escape();
}

void driver::step_move_and_draw(
	double _delta
) {

	if(input.is_tab()) {

		build_message("color selection");
		mode=modes::color_selection;
		step_color_selection(_delta);
		return;
	}

	cursor_blink_timer+=_delta;
	if(cursor_blink_timer > cursor_blink_cycle_len) {

		cursor_blink_timer=0.0;
	}

	//cursor movement...
	int x=0, y=0;

	if(input.is_up()) {

		y--;
	}
	else if(input.is_down()) {

		y++;
	}
	else if(input.is_left()) {
	
		x--;
	}
	else if(input.is_right()) {
	
		x++;
	}

	if(x) {

		int attempted_x=cursor.x+x;
		if(attempted_x >= 0 && attempted_x < canvas.get_width()) {

			cursor.x=attempted_x;
		}
	}

	if(y) {

		int attempted_y=cursor.y+y;
		if(attempted_y >= 0 && attempted_y < canvas.get_height()) {

			cursor.y=attempted_y;
		}
	}

	//manage painting...
	if(input.is_space()) {

		canvas.set(cursor.x, cursor.y, bgcolor, fgcolor, shape);
	}
}

void driver::step_color_selection(
	double _delta
) {

	if(input.is_escape()) {

		build_message("normal");
		mode=modes::move_and_draw;
		return;
	}

	if(input.is_up()) {

		cycle_color(bgcolor, -1);
	}
	else if(input.is_down()) {

		cycle_color(bgcolor, 1);
	}
	else if(input.is_left()) {
	
		cycle_color(fgcolor, -1);
	}
	else if(input.is_right()) {
	
		cycle_color(fgcolor, 1);
	}
}

void driver::sync_display() {

	sync_canvas_display();
	sync_drawer_display();
	sync_statusbar_display();
	sync_cursor_position();
}

void driver::sync_cursor_position() {

	const int	pos_y=6,
				pos_x=canvas.get_width()+2;
	const int	bg=colors::black,
				fg=colors::white;


	std::stringstream ss;
	ss<<std::setfill('0')<<std::setw(3)<<cursor.x<<","
		<<std::setw(3)<<cursor.y;

	window.set_text(pos_x, pos_y, bg, fg, ss.str());
}

void driver::sync_drawer_display() {

	const int separator_x=canvas.get_width();
	for(int y=0; y < canvas.get_height(); y++) {

		window.set(separator_x, y, colors::white, colors::white, ' ');
	}

	//Foreground colors...
	const int fg_color_y=2;
	for(int x=colors::color_min+1; x < colors::color_max; x++) {

		bool current=x==fgcolor;
		char type=current ? 'v' : ' ';
		int tick_color=current ? app::get_contrasting_color(x) : colors::black;
		window.set(canvas.get_width()+1+x, fg_color_y, x, tick_color, type);
	}

	//Background colors...
	const int bg_color_y=4;
	for(int x=colors::color_min+1; x < colors::color_max; x++) {
	
		bool current=x==bgcolor;
		char type=current ? 'v' : ' ';
		int tick_color=current ? app::get_contrasting_color(x) : colors::black;
		window.set(canvas.get_width()+1+x, bg_color_y, x, tick_color, type);
	}

	//TODO: Current shape.
}

void driver::sync_statusbar_display() {

	int statusbar_bg=colors::white;
	int statusbar_fg=colors::blue;
	int statusbar_y=window.get_h()-status_bar_height;

	for(int x=0; x<window.get_w(); x++) {

		window.set(+x, statusbar_y, statusbar_bg, statusbar_fg, ' ');
	}

	//TODO: of course, this would only get updated when changes to the bar 
	//go off!!
	window.set_text(1, statusbar_y, statusbar_bg, statusbar_fg, message);
}

void driver::cycle_color(
	int& _color,
	int _direction
) {

	_color+=_direction;
	if(_color==colors::color_min) {

		_color=colors::color_max-1;
		return;
	}

	if(_color==colors::color_max) {

		_color=colors::color_min+1;
		return;
	}
}

void driver::sync_canvas_display() {

	for(int y=0; y < canvas.get_height(); y++) {

		for(int x=0; x < canvas.get_width(); x++) {

			const auto cell=canvas.get(x, y);
			window.set(x, y, cell.bg, cell.fg, cell.contents);
		}
	}

	//of course, the cursor now...
	//TODO: When the time comes, mark this chunk as "update".
	if(cursor_blink_timer > (cursor_blink_cycle_len / 2)) {

		uint8_t cursor_color=colors::white;
		//TODO: Add bg color too!!

		auto cursor_contents=canvas.get(cursor.x, cursor.y).contents;
		window.set(cursor.x, cursor.y, cursor_color, cursor_color, cursor_contents);
	}
}
