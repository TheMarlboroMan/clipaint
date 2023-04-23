#include "app/canvas.h"
#include <stdexcept>
#include <sstream>

using namespace app;

canvas::canvas(
	int _w,
	int _h
)
	:width(_w),
	height(_h),
	cells{std::size_t(_w*_h)} {

}

canvas& canvas::set(
	uint8_t _x,
	uint8_t _y,
	uint8_t _bg,
	uint8_t _fg,
	char _c
) {

	auto index=coordinates_to_index(_x, _y);
	cells[index]={_bg, _fg, _c};
	return *this;
}

canvas& canvas::set_bg(
	uint8_t _x,
	uint8_t _y,
	uint8_t _bg
) {

	auto index=coordinates_to_index(_x, _y);
	cells[index].bg=_bg;
	return *this;
}

canvas& canvas::set_fg(
	uint8_t _x,
	uint8_t _y,
	uint8_t _fg
) {

	auto index=coordinates_to_index(_x, _y);
	cells[index].fg=_fg;
	return *this;
}

canvas& canvas::set_contents(
	uint8_t _x,
	uint8_t _y,
	char _contents
) {

	auto index=coordinates_to_index(_x, _y);
	cells[index].contents=_contents;
	return *this;
}

const cell& canvas::get(
	uint8_t _x,
	uint8_t _y
) const {

	auto index=coordinates_to_index(_x, _y);

	try {

		return cells.at(index);
	}
	catch(std::exception& e) {

		std::stringstream ss;
		ss<<"failed to get index "<<index<<" from canvas, corresponding to x="<<_x<<", y="<<_y<<"...";
		throw std::runtime_error(ss.str());
	}
}

std::size_t canvas::coordinates_to_index(
	uint8_t _x,
	uint8_t _y
) const {

	return (_y * width) + _x;
}
