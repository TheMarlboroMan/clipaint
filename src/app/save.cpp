#include "app/save.h"
#include "app/canvas.h"
#include <cstdint>

using namespace app;

void app::save(
	const canvas& _canvas,
	std::ostream& _stream
) {

	const uint8_t heading{240};
	//marker, a non-printable character.
	_stream.put(static_cast<char>(heading));

	//add marker: four bytes as "clip"...
	_stream<<"clip";

	//next the version as an unsigned integer, a byte...
	const uint8_t version=1;
	_stream.put(static_cast<char>(version));

	//next width and height, same, two bytes
	const uint16_t w=_canvas.get_width();
	const uint16_t h=_canvas.get_height();

	_stream.write(reinterpret_cast<const char*>(&w), sizeof(w));
	_stream.write(reinterpret_cast<const char*>(&h), sizeof(h));

	//cells are added top to bottom, left to right. Each cell has two bytes,
	//one for bg/fg colors (4 bits each) and another for the contents,
	//adding up to two bytes per cell.
	for(uint8_t y=0; y<h; y++) {

		for(uint8_t x=0; x<w; x++) {

			const auto cell=_canvas.get(x, y);
			
			uint8_t fg{cell.fg};
			uint8_t bg{cell.bg};
			fg<<=4; //shift the foreground 4 bits to the left so both can be combined.
			uint8_t both=fg|bg;	

			_stream.put(static_cast<char>(both));
			_stream.put(static_cast<char>(cell.contents));
		}
	} 
}
