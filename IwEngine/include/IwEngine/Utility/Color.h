#pragma once

#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace Utility {
	//Codes are diffrent outside of windows
	enum ConsoleColorCode {
		BLACK,
		BLUE,
		GREEN,
		AQUA,
		RED,
		PURPLE,
		YELLOW,
		WHITE,
		GRAY,
		LIGHT_BLUE,
		LIGHT_GREEN,
		LIGHT_AGUA,
		LIGHT_RED,
		LIGHT_PURPLE,
		LIGHT_YELLOW,
		BRIGHT_WHITE
	};

	class ConsoleColorModifier {
	private:
		int color;
	public:
		ConsoleColorModifier(ConsoleColorCode fg, ConsoleColorCode bg) : color(bg * 16 + fg) {};
		friend std::ostream& operator<<(std::ostream& os, const ConsoleColorModifier& mod) {
#ifdef _WIN32
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, mod.color);
			return os;
#else
			return os << "\033[" << mod.color << "m"; //this will be the wrong color
#endif
		}
	};
}