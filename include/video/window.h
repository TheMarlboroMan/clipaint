#pragma once
#include "app/colors.h"
#include "app/shapes.h"
#include <ostream>
#include <vector>
#include <cstdint>

namespace video {

struct cell {

	public:
	uint8_t				bg{app::black}, fg{app::black}, type{app::nothing};
};

class window {
	
	public:

						window(int, int);
	int					get_w() const {return width;}
	int					get_h() const {return height;}
	//!sets the given cell.
	void				set(int, int, uint8_t, uint8_t, uint8_t);
	//!causes the whole buffer to be printed
	void				draw(std::ostream&);
	//!resets the contents of the whole buffer to nothing.
	void				clear();
	void				reset(std::ostream&);

	private:

	int					width{0}, height{0};
	std::vector<cell>	cells;
};

}
