#pragma once
#include <tools/terminal_in.h>

namespace input {

class input {

	public:

	void					loop();
	bool					is_escape() const {return control_flags & cflags::escape;}
	bool					is_up() const {return control_flags & cflags::up;}
	bool					is_down() const {return control_flags & cflags::down;}
	bool					is_left() const {return control_flags & cflags::left;}
	bool					is_right() const {return control_flags & cflags::right;}
	bool					is_space() const {return control_flags & cflags::space;}
	bool					is_tab() const {return control_flags & cflags::tab;}
	bool					is_one() const {return control_flags & cflags::one;}
	bool					is_two() const {return control_flags & cflags::two;}
	bool					is_three() const {return control_flags & cflags::three;}
	bool 					is_char() const {return curchar;}
	char					get_char() const {return curchar;}

	private:
	
	enum cflags {
		escape=1,
		up=2,
		down=4,
		left=8,
		right=16,
		space=32,
		tab=64,
		one=128,
		two=256,
		three=512,
	};

	tools::terminal_in		in;
	int control_flags{0};
	char curchar{0};
};
}
