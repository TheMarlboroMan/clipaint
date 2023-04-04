#include "video/window.h"
#include <tools/terminal_out.h>
#include <stdexcept>
#include <sstream>

using namespace video;

window::window(
	int _w,
	int _h
): width{_w}, height{_h}, cells{_w*_h} {

	if(_w <=0 || _h <=0 ) {

		throw std::runtime_error("bad viewport size: width and height must be larger than zero");
	}
}

void window::set(
	int _x, 
	int _y,
	uint8_t _bg,
	uint8_t _fg,
	uint8_t _type
) {

	std::size_t index=_x + (width * _y);
	
	if(index >= cells.size()) {

		std::stringstream errmsg;
		errmsg<<"cannot set cell at "<<_x<<","<<_y<<": out of bounds";
		throw std::runtime_error(errmsg.str());
	}

	cells[index].bg=_bg;
	cells[index].fg=_fg;
	cells[index].type=_type;
}

void window::draw(
	std::ostream& _out
) {

	uint8_t bg{tools::bg_black}, fg{tools::txt_white};

	_out<<tools::s::pos(1, 1)
		<<tools::s::background_color(bg)
		<<tools::s::text_color(fg);

	std::size_t x=0;
	for(const auto c : cells) {

		++x;

		if(bg!=c.bg) {

			bg=c.bg;
			switch(bg) {

				case app::black: _out<<tools::s::background_color(tools::bg_black); break;
				case app::red:	_out<<tools::s::background_color(tools::bg_red); break;
				case app::green:	_out<<tools::s::background_color(tools::bg_green); break;
				case app::yellow:_out<<tools::s::background_color(tools::bg_yellow); break;
				case app::blue:	_out<<tools::s::background_color(tools::bg_blue); break;
				case app::magenta: _out<<tools::s::background_color(tools::bg_magenta); break;
				case app::cyan:	_out<<tools::s::background_color(tools::bg_cyan); break;
				case app::white: _out<<tools::s::background_color(tools::bg_white); break;
			}
		}

		if(fg!=c.fg) {

			fg=c.fg;
			switch(fg) {

				case app::black: _out<<tools::s::text_color(tools::txt_black); break;
				case app::red:	_out<<tools::s::text_color(tools::txt_red); break;
				case app::green:	_out<<tools::s::text_color(tools::txt_green); break;
				case app::yellow:_out<<tools::s::text_color(tools::txt_yellow); break;
				case app::blue:	_out<<tools::s::text_color(tools::txt_blue); break;
				case app::magenta: _out<<tools::s::text_color(tools::txt_magenta); break;
				case app::cyan:	_out<<tools::s::text_color(tools::txt_cyan); break;
				case app::white: _out<<tools::s::text_color(tools::txt_white); break;
			}
		}

		switch(c.type) {

			case app::nothing: _out<<" "; break;
			case app::solid: _out<<"█"; break;
			case app::v: _out<<"v"; break;
			default: _out<<"?"; break;
		}

		if(x==width) {

			_out<<std::endl;
			x=0;
		}
	}
}

void window::reset(
	std::ostream&  _out
) {

	_out<<tools::s::reset();
}

void window::clear() {

	for(auto& curcell : cells) {

		curcell=cell{};
	}
}
