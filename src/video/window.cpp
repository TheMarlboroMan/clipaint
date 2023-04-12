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

	modified_cells.reserve(width*height);
}

void window::set(
	int _x, 
	int _y,
	uint8_t _bg,
	uint8_t _fg,
	char _type
) {

	std::size_t index=_x + (width * _y);
	
	if(index >= cells.size()) {

		std::stringstream errmsg;
		errmsg<<"cannot set cell at "<<_x<<","<<_y<<": out of bounds";
		throw std::runtime_error(errmsg.str());
	}

	auto& cell=cells[index];

	if(cell.bg==_bg && cell.fg==_fg && cell.contents==_type) {

		return;
	}

	cells[index].bg=_bg;
	cells[index].fg=_fg;
	cells[index].contents=_type;
	modified_cells.push_back({_x, _y});
}

void window::set_text(
	int _x, 
	int _y,
	uint8_t _bg,
	uint8_t _fg,
	const std::string& _text
) {

	std::size_t i=0;
	
	//do make sure we are not extending beyond the window bounds...
	while(i < _text.length() && i < width) {

		set(_x+i, _y, _bg, _fg, _text.at(i));	
		i++;
	}
}

void window::refresh(
	std::ostream& _out
) {

	if(refresh_all) {

		draw(_out);
		return;
	}

	if(!modified_cells.size()) {

		return;
	}

	for(const auto& mod : modified_cells) {

		std::size_t index=mod.x + (width * mod.y);
		const auto& cell=cells[index];
		_out<<tools::s::pos(mod.x+1, mod.y+1)
			<<tools::s::background_color(color_to_bg_termcolor(cell.bg))
			<<tools::s::text_color(color_to_fg_termcolor(cell.fg))
			<<cell.contents;
	}

	modified_cells.clear();	
	std::flush(_out);
}

void window::draw(
	std::ostream& _out
) {

	uint8_t bg{tools::bg_black}, fg{tools::txt_white};

	_out<<tools::s::pos(1, 1)
		<<tools::s::background_color(bg)
		<<tools::s::text_color(fg);

	std::size_t x=0, y=0;
	for(const auto c : cells) {

		++x;

		if(bg!=c.bg) {

			bg=c.bg;
			_out<<tools::s::background_color(color_to_bg_termcolor(bg));
		}

		if(fg!=c.fg) {

			fg=c.fg;
			_out<<tools::s::text_color(color_to_fg_termcolor(fg));
		}

		_out<<c.contents;

		if(x==width && y!=height-1) {

			_out<<"\n";
			++y;
			x=0;
		}
	}

	std::flush(_out);
	modified_cells.clear();
	refresh_all=false;
}

int window::color_to_fg_termcolor(
	int _color
) const {

	switch(_color) {

		case app::black:return tools::txt_black;
		case app::red:return tools::txt_red;
		case app::green:return tools::txt_green;
		case app::yellow:return tools::txt_yellow;
		case app::blue:return tools::txt_blue;
		case app::magenta:return tools::txt_magenta;
		case app::cyan:return tools::txt_cyan;
		case app::white:return tools::txt_white;
	}

	return tools::txt_red;
}

int window::color_to_bg_termcolor(
	int _color
) const {

	switch(_color) {

		case app::black:return tools::bg_black;
		case app::red:return tools::bg_red;
		case app::green:return tools::bg_green;
		case app::yellow:return tools::bg_yellow;
		case app::blue:return tools::bg_blue;
		case app::magenta:return tools::bg_magenta;
		case app::cyan:return tools::bg_cyan;
		case app::white:return tools::bg_white;
	}

	return tools::bg_red;
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

	refresh_all=true;
}
