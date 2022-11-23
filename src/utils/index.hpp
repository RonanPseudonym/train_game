#include <fstream>
#include <string>

namespace Utils {
	namespace Bitwise {
		template <typename T>
		void    PrintBinary                 (T num);

		// uint8_t IfstreamToLittleEndianByte  (std::ifstream& _file);
		int     IfstreamToLittleEndianInt   (std::ifstream& _file);
		int     IfstreamToBigEndianInt      (std::ifstream& _file);
		double  IfstreamToLittleEndianDouble(std::ifstream& _file);
	}

	namespace UI {
		void Ok     (std::string text);
		void Note   (std::string text);
		void Warning(std::string text);
		void Debug  (std::string text);
		void Error  (std::string text, int error_code);

		namespace Color { // On the one hand, these are not universal, so I probably shouldn't be using them. On the other hand, they look pretty.
			const std::string ESCAPE = "\033[";
			const std::string ENDING = "m";

			enum AnsiColorCode {
				RESET = 0,
				BOLD,
				UNDERLINE,
				INVERSE,
				BLACK = 30,
				RED,
				GREEN,
				YELLOW,
				BLUE,
				MAGENTA,
				CYAN,
				WHITE
			};

			std::string Compile(AnsiColorCode ansi_color_code);
		}
	}
}