#include "app/colors.h"

using namespace app;

int app::get_contrasting_color(
	int _color
) {

	switch(_color) {

		case colors::black: return colors::white;
		case colors::red:	return colors::white;
		case colors::green: return colors::black;
		case colors::yellow: return colors::black;
		case colors::blue: return colors::black;
		case colors::magenta: return colors::black;
		case colors::cyan: return colors::black;
		case colors::white: return colors::black;
	}

	return colors::black;
}
