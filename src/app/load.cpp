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
	char data{0};

	_file.get(data);
	uint8_t heading=static_cast<uint8_t>(data),
			expected{240};
	std::cout<<data<<" "<<heading<<" "<<(int)data<<" "<<(int)heading<<" "<<(int)expected<<std::endl;
	
	if(heading!=expected){

		throw std::runtime_error("bad heading character");
	}

	char clip[4]={0,0,0,0};
	_file.get(clip, 4);

	if(clip[0]!='c' || clip[1]!='l' || clip[2]!='i' || clip[3]!='p') {

		throw std::runtime_error("bad heading type");
	}

	_file.get(data);
	uint8_t version{data};
	std::cout<<"version is "<<version<<std::endl;

	_file.get(data);
	uint8_t w{data};

	_file.get(data);
	uint8_t h{data};

	//TODO: set canvas size now!
	//
	//TODO: load, load load load load load load.
}
