#include "../../index.hpp"

/*
	Position |    Field   | Value |  Type   | Number | Order

	Byte 0   | Shape Type | 1     | Integer | 1      | Little
	Byte 4   | X          | X     | Double  | 1      | Little
	Byte 12  | Y          | Y     | Double  | 1      | Little
*/

void Shapefile::Shp::Shape::Point::Parse(std::ifstream& _file) {
	record_number  = Utils::Bitwise::IfstreamToBigEndianInt(_file);
	content_length = Utils::Bitwise::IfstreamToBigEndianInt(_file);

	if (Utils::Bitwise::IfstreamToLittleEndianInt(_file) != static_cast<int>(Shapefile::General::POINT)) {
		Utils::UI::Error("The currently parsing shapefile document is of a 'Point' type, but this record reads as not a Point (bytes 0-4 should be 1)", 3);
	}

	x = Utils::Bitwise::IfstreamToLittleEndianDouble(_file);
	y = Utils::Bitwise::IfstreamToLittleEndianDouble(_file);


	#ifdef DEBUG_TEXT

	std::cout << std::endl;
	Utils::UI::Note(Utils::UI::Color::Compile(Utils::UI::Color::BOLD)+"New Record");
	Utils::UI::Note("X: " + std::to_string(x));
	Utils::UI::Note("Y: " + std::to_string(y));

	#endif
}