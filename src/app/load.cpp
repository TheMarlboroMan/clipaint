#include "app/load.h"
#include "app/canvas.h"
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include <iostream>

using namespace app;

void app::load(
	canvas& _canvas,
	std::istream& _file
) {

	//assume the file cursor is at the beginning of the stream.
	auto get_u8=[&_file]() -> uint8_t {

		char data{0};
		_file.get(data);
		return static_cast<uint8_t>(data);
	};

	auto get_u16=[&_file]() -> uint16_t {

		char buf[2]={0,0};
		_file.get(buf[0]);
		_file.get(buf[1]);
		return * reinterpret_cast<uint16_t*>(buf);
	};

	uint8_t heading=get_u8(),
			expected{240};
	
	if(heading!=expected){

		throw std::runtime_error("bad heading character");
	}

	//get will grab n-1 and add a null terminator, thus 5 bytes are needed.
	char clip[5]={0,0,0,0,0};
	_file.get(clip, 5);

	if(clip[0]!='c' || clip[1]!='l' || clip[2]!='i' || clip[3]!='p') {

		throw std::runtime_error("bad heading type");
	}

	auto version=get_u8();
	auto w=get_u16();
	auto h=get_u16();

	int canvas_w=static_cast<int>(w);
	int canvas_h=static_cast<int>(h);
	app::canvas newcanvas{canvas_w, canvas_h};

	for(int y=0; y<canvas_h; y++) {

		for(int x=0; x<canvas_w; x++) {

			auto colors=get_u8();
			char contents={0};
			_file.get(contents);

			//separate colors, the first 4 bits are foreground, the rest bg.
			uint8_t fg{colors}, bg{colors};
			bg&=0b00001111;

			fg&=0b11110000;
			fg>>=4;

			newcanvas.set(x, y, bg, fg, contents);
		}
	}

	_canvas=std::move(newcanvas);
}
