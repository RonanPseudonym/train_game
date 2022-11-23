#include "../index.hpp"
#include <iostream>

void PrettyPrint(Utils::UI::Color::AnsiColorCode ansi_color_code, std::string tooltip, std::string text) {
	std::cout << 
	Utils::UI::Color::Compile(ansi_color_code) << 
	Utils::UI::Color::Compile(Utils::UI::Color::BOLD) <<
	"[" << tooltip << "] " << 
	Utils::UI::Color::Compile(Utils::UI::Color::RESET) <<
	Utils::UI::Color::Compile(ansi_color_code) << 
	text << 
	Utils::UI::Color::Compile(Utils::UI::Color::RESET) 
	<< std::endl;
}

void Utils::UI::Ok(std::string text)      { PrettyPrint(Utils::UI::Color::GREEN,  "OK",      text); }
void Utils::UI::Warning(std::string text) {	PrettyPrint(Utils::UI::Color::YELLOW, "WARNING", text); }
void Utils::UI::Note(std::string text)    {	PrettyPrint(Utils::UI::Color::CYAN,   "NOTE",    text); }
void Utils::UI::Debug(std::string text)   {	PrettyPrint(Utils::UI::Color::MAGENTA,"DEBUG",   text); }

void Utils::UI::Error(std::string text, int error_code) {
	PrettyPrint(Utils::UI::Color::RED, "ERROR", text); 
	
	if (error_code) {
		std::exit(error_code);
	}
}