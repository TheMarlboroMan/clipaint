#pragma once
#include <tools/terminal_in.h>

namespace input {

class input {

	public:

	void					loop();
	bool					is_exit() const {return control_flags & cflags::escape;}
	bool					is_up() const {return control_flags & cflags::up;}
	bool					is_down() const {return control_flags & cflags::down;}
	bool					is_left() const {return control_flags & cflags::left;}
	bool					is_right() const {return control_flags & cflags::right;}
	bool					is_space() const {return control_flags & cflags::space;}

	private:
	
	enum cflags {
		escape=1,
		up=2,
		down=4,
		left=8,
		right=16,
		space=32
	};

	tools::terminal_in		in;
	int control_flags{0};
};
}
