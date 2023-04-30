#include "input/input.h"

using namespace input;

void input::input::loop() {
	
	curchar=0;
	auto input_data=in.get();

	control_flags=0;
	if(!input_data) {
	
		return;
	}

	if(input_data.type==input_data.types::control) {

		if(input_data.control==input_data.controls::escape) {

			control_flags|=cflags::escape;
		}

		if(input_data.control==input_data.controls::tab) {

			control_flags|=cflags::tab;
		}
	}

	if(input_data.type==input_data.types::chr) {

		curchar=input_data.get_string_data()[0];

		switch(curchar) {
			case ' ':
				control_flags|=cflags::space;
			break;
			case '1':
				control_flags|=cflags::one;
			break;
			case '2':
				control_flags|=cflags::two;
			break;
			case '3':
				control_flags|=cflags::three;
			break;
		}
	}

	if(input_data.type==input_data.types::arrow) {

		if(input_data.arrow==input_data.arrowkeys::up) {
	
			control_flags|=cflags::up;
		}

		if(input_data.arrow==input_data.arrowkeys::down) {
	
			control_flags|=cflags::down;
		}

		if(input_data.arrow==input_data.arrowkeys::left) {
	
			control_flags|=cflags::left;
		}

		if(input_data.arrow==input_data.arrowkeys::right) {
	
			control_flags|=cflags::right;
		}
	}
}

