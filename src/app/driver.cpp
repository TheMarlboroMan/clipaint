#include "app/driver.h"
#include "app/colors.h"
#include "app/shapes.h"
#include <stdexcept>

using namespace app;

driver::driver(
	video::window& _window,
	const input::input& _input,
	int _drawer_w
):
	canvas{_window.get_w()-_drawer_w, _window.get_h()},
	window{_window},
	input{_input},
	drawer_width(_drawer_w)
{
	sync_display();
}

void driver::step() {

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
		if(attempted_x > 0 && attempted_x < canvas.get_width()) {

			cursor.x=attempted_x;
		}
	}

	if(y) {

		int attempted_y=cursor.y+y;
		if(attempted_y > 0 && attempted_y < canvas.get_height()) {

			cursor.y=attempted_y;
		}
	}

	//manage painting...
	if(input.is_space()) {

		canvas.set(cursor.x, cursor.y, bgcolor, fgcolor, shape);
	}

	//
}

void driver::sync_display() {

	sync_canvas_display();
	sync_drawer_display();
}

void driver::sync_drawer_display() {

	int x=canvas.get_width();
	for(int y=0; y < canvas.get_height(); y++) {

		window.set(x, y, colors::white, colors::white, types::solid);
	}

	//TODO: These should be like... spinners???
	//TODO: Black tick with black color is stupid.
	//TODO: Create colors::contrast_with method.
	//Foreground colors...
	const int fg_color_y=2;
	for(int x=colors::color_min+1; x < colors::color_max; x++) {

		int type=x==fgcolor ? types::v : types::nothing;
		window.set(canvas.get_width()+1+x, fg_color_y, x, colors::black, type);
	}

	//Background colors...
	const int bg_color_y=4;
	for(int x=colors::color_min+1; x < colors::color_max; x++) {

		int type=x==bgcolor ? types::v : types::nothing;
		window.set(canvas.get_width()+1+x, bg_color_y, x, colors::black, type);
	}

	//TODO: Current shape.
}

void driver::sync_canvas_display() {

	uint8_t bg=colors::black;
	uint8_t fg=colors::white;
	uint8_t type=types::solid;

	for(int y=0; y < canvas.get_height(); y++) {

		for(int x=0; x < canvas.get_width(); x++) {

			const auto cell=canvas.get(x, y);

			//This is mostly stupid because values are the same, but well...
			switch(cell.bg) {

				case colors::black: bg=colors::black; break;
				case colors::red: bg=colors::red; break;
				case colors::green: bg=colors::green; break;
				case colors::yellow: bg=colors::yellow; break;
				case colors::blue: bg=colors::blue; break;
				case colors::magenta: bg=colors::magenta; break;
				case colors::cyan: bg=colors::cyan; break;
				case colors::white: bg=colors::white; break;
				default: throw std::runtime_error("invalid cell bg");
			}

			switch(cell.fg) {

				case colors::black: fg=colors::black; break;
				case colors::red: fg=colors::red; break;
				case colors::green: fg=colors::green; break;
				case colors::yellow: fg=colors::yellow; break;
				case colors::blue: fg=colors::blue; break;
				case colors::magenta: fg=colors::magenta; break;
				case colors::cyan: fg=colors::cyan; break;
				case colors::white: fg=colors::white; break;
				default: throw std::runtime_error("invalid cell fg");
			}

			//TODO: sync also the type, which right now is a char... Maybe it should be a char allright,.
			window.set(x, y, bg, fg, type);
		}
	}

	//of course, the cursor now...
	uint8_t cursor_color=colors::white;
	//TODO: Should show the shape under the cursor, if any.
	window.set(cursor.x, cursor.y, cursor_color, cursor_color, types::nothing);
}
