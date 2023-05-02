#include "video/window.h"
#include "input/input.h"
#include "app/driver.h"
#include <tools/arg_manager.h>
#include <tools/terminal_out.h>
#include <lm/log.h>
#include <lm/file_logger.h>
#include <thread>
#include <iostream>
#include <sstream>

struct user_arg {

	bool show_help{false},
		show_size{false};
	int canvas_w{30}, 
		canvas_h{20};
};

void	show_help();
void	show_size();
user_arg parse_args(int, char **);

int main(
	int argc, 
	char ** argv
) {

	lm::file_logger logger("log.log");

	try {

		user_arg ua=parse_args(argc, argv);
		if(ua.show_help) {

			show_help();
			return 0;
		}

		if(ua.show_size) {

			show_size();
			return 0;
		}

		int drawer_w=10,
			statusbar_h=1;

		auto ts=tools::get_termsize();
		video::window display(ts.w, ts.h);

		//TODO: The terminal should scroll down...
		input::input in;
		auto now=std::chrono::system_clock::now();
		auto then=now;
		double draw_ms_elapsed{0.0};

		app::driver driver(display, in, ua.canvas_w, ua.canvas_h, drawer_w, statusbar_h);
		driver.load("drawing");
		return 0;
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
				display.refresh(std::cout);
			}
		}

		return 0;
	}
	catch(std::exception& e) {

		std::stringstream ss;
		ss<<"something failed: "<<e.what();
		lm::log(logger).error()<<ss.str();
		std::cerr<<ss.str()<<std::endl;
		return 1;
	}
}

user_arg parse_args(
	int _argc, 
	char ** _argv
) {

	tools::arg_manager argman(_argc, _argv);
	user_arg result;

	if(argman.exists("--help")) {

		result.show_help=true;
		return result;
	}

	if(argman.exists("--size")) {

		result.show_size=true;
		return result;
	}

	auto checkarg=[&](const char * _argname) -> bool {

		return argman.exists(_argname) && argman.arg_follows(_argname);
	};

	if(checkarg("--width")) {

		result.canvas_w=std::stoi(argman.get_following("--width"));
	}
	
	if(checkarg("--height")) {

		result.canvas_h=std::stoi(argman.get_following("--height"));
	}

	return result;
}

void show_help() {

	std::cout<<
	"--help: shows this help\n"
	"--size: outputs the current terminal size\n"
	"--width n: sets the width of the canvas\n"
	"--height n: sets the height of the canvas\n";

	std::flush(std::cout);
}

void show_size() {

	auto ts=tools::get_termsize();
	std::cout<<"width:"<<ts.w<<" height:"<<ts.h<<std::endl;
}
