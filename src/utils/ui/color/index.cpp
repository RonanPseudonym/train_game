#include "../../index.hpp"
#include <iostream>

std::string Utils::UI::Color::Compile(Utils::UI::Color::AnsiColorCode ansi_color_code) {
	return (
		Utils::UI::Color::ESCAPE +
		std::to_string(static_cast<int>(ansi_color_code)) +
		Utils::UI::Color::ENDING
	);
}