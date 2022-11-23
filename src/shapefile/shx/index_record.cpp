#include "../index.hpp"
#include "../../config.hpp"
#include <iostream>

/*
	Position |     Field      |      Value     |  Type   | Order

	Byte 0   | Offset         | Offset         | Integer | Big
	Byte 4   | Content Length | Content Length | Integer | Big
*/

Shapefile::Shx::IndexRecord::IndexRecord() {

}

void Shapefile::Shx::IndexRecord::Parse(std::ifstream& _file) {
	offset         = Utils::Bitwise::IfstreamToBigEndianInt(_file);
	content_length = Utils::Bitwise::IfstreamToBigEndianInt(_file);

	#ifdef DEBUG_TEXT

	std::cout << std::endl;
	Utils::UI::Note(Utils::UI::Color::Compile(Utils::UI::Color::BOLD)+"New Index Record");
	Utils::UI::Note("Offset:         " + std::to_string(offset));
	Utils::UI::Note("Content Length: " + std::to_string(content_length));

	#endif
}