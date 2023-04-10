#pragma once
#include "app/colors.h"
#include <ostream>
#include <vector>
#include <cstdint>
#include <string>

namespace video {

struct cell {

	public:
	uint8_t				bg{app::black}, fg{app::black};
	char				contents{' '};
};

class window {
	
	public:

						window(int, int);
	int					get_w() const {return width;}
	int					get_h() const {return height;}
	//!sets the given cell.
	void				set(int, int, uint8_t, uint8_t, char);
	void				set_text(int, int, uint8_t, uint8_t, const std::string&);
	//!causes the whole buffer to be printed
	void				draw(std::ostream&);
	//!causes a refresh of the modified parts of the buffer.
	void				refresh(std::ostream&);
	//!resets the contents of the whole buffer to nothing.
	void				clear();
	void				reset(std::ostream&);

	private:

	int					color_to_fg_termcolor(int) const;
	int					color_to_bg_termcolor(int) const;

	struct mod_cell{
		int x, y;
	};

	int					width{0}, height{0};
	std::vector<cell>	cells;
	std::vector<mod_cell>	modified_cells;
	bool refresh_all{true};
};

}
