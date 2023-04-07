#pragma once
#include "colors.h"
#include <vector>
#include <cstdint>

namespace app {

/**
 * a cell is the minimal component of a canvas.
 * it consists of a background color, a foreground color and a char that will
 * be "painted".
 */
struct cell {

	public:

	uint8_t				fg{colors::black}, bg{colors::black};
	//TODO: yeah, no, the window says a type...
	char				contents{' '};
};

class canvas {

	public:

						canvas(int, int);
	int					get_width() const {return width;}
	int					get_height() const {return height;}
	canvas&				set(uint8_t, uint8_t, uint8_t, uint8_t, char);
	canvas&				set_bg(uint8_t, uint8_t, uint8_t);
	canvas&				set_fg(uint8_t, uint8_t, uint8_t);
	canvas&				set_contents(uint8_t, uint8_t, char);
	const cell&			get(uint8_t, uint8_t) const;

	private:

	std::size_t			coordinates_to_index(uint8_t, uint8_t) const;

	int 				width{0},
						height{0};
	std::vector<cell>	cells;
};
}
