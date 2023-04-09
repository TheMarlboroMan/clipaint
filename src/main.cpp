#include <iostream>
#include "video/window.h"
#include "input/input.h"
#include "app/driver.h"
#include <thread>

int main(int /*argc*/, char ** /*argv*/) {

	int canvas_w=30, 
		canvas_h=20;
	int drawer_w=10,
		statusbar_h=1;
	video::window display(canvas_w+drawer_w, canvas_h+statusbar_h);

	//TODO: The terminal should scroll down...
	input::input in;
	auto now=std::chrono::system_clock::now();
	auto then=now;
	double draw_ms_elapsed{0.0};

	app::driver driver(display, in, drawer_w, statusbar_h);
	display.clear();

	while(true) {

		in.loop();
		if(driver.is_exit()) {

			break;
		}

		//run logic..
		then=std::chrono::system_clock::now();
		std::chrono::duration<double> diff=then-now;
		now=then;

		double delta=diff.count();
		driver.step(delta);

		//draw
		draw_ms_elapsed+=delta;
		if(draw_ms_elapsed >= 0.1) {

			//TODO: You sure about this???
			driver.sync_display();
			draw_ms_elapsed=0.0;
			display.draw(std::cout);
		}
	}

	return 0;
}
