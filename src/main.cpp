#include <iostream>
#include "video/window.h"
#include "input/input.h"
#include "app/driver.h"
#include <thread>

int main(int /*argc*/, char ** /*argv*/) {

	//TODO: Some of these will be the canvas, some would be
	//the status with x, y, background, foreground and... symbol?
	int w=30, h=20;
	video::window display(w, h);
	//puerile attempt to scroll down a lot of lines... Maybe not enough.
	for(int i=0; i<h; i++) {std::cout<<std::endl;}

	input::input in;
	auto now=std::chrono::system_clock::now();
	auto then=now;
	double draw_ms_elapsed{0.0};

	app::driver driver(display, in);
	display.clear();

	while(true) {

		in.loop();
		if(in.is_exit()) {

			break;
		}

		//run logic..
		then=std::chrono::system_clock::now();
		std::chrono::duration<double> diff=then-now;
		now=then;

		driver.step();

		//draw
		draw_ms_elapsed+=diff.count();
		if(draw_ms_elapsed >= 0.1) {

			//TODO: You sure about this???
			driver.sync_display();
			draw_ms_elapsed=0.0;
			display.draw(std::cout);
		}
	}

	return 0;
}
