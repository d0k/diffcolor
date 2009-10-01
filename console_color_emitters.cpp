//===========================================================================//
// (c) Benjamin Kramer
// This file is distributed under the MIT License. See LICENSE for details.
//===========================================================================//

#include "color_emitter.h"

#include <iostream>
#include <cassert>

std::ostream& operator<<(std::ostream& os,
                         ColorEmitter::ColorManipulator cm) {
	cm.emitColor(os);
	return os;
}

#ifdef _WIN32

#include <windows.h>

static WORD getColors() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.wAttributes;
	return 0;
}

WindowsColorEmitter::WindowsColorEmitter() : oldcolor(getColors()) {
}

WindowsColorEmitter::~WindowsColorEmitter() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), oldcolor);
}

void WindowsColorEmitter::emitColor(std::ostream &os, ColorEmitter::Color c,
                                    bool background) {
	assert(os == std::cout && "Works only on cout");
	WORD colors = getColors();
	if (c == ColorEmitter::STANDARD) {
		colors = oldcolor;
	} else {
		if (background) {
			colors = colors & ~BACKGROUND_RED & ~BACKGROUND_GREEN &
			                  ~BACKGROUND_BLUE & ~BACKGROUND_INTENSITY;
			colors |= ((c & 1) ? BACKGROUND_RED : 0) |
			          ((c & 2) ? BACKGROUND_GREEN : 0 ) |
			          ((c & 4) ? BACKGROUND_BLUE : 0) |
			          BACKGROUND_INTENSITY;
		} else {
			colors = colors & ~FOREGROUND_RED & ~FOREGROUND_GREEN &
			                  ~FOREGROUND_BLUE & ~FOREGROUND_INTENSITY;
			colors |= ((c & 1) ? FOREGROUND_RED : 0) |
			          ((c & 2) ? FOREGROUND_GREEN : 0 ) |
			          ((c & 4) ? FOREGROUND_BLUE : 0) |
			          FOREGROUND_INTENSITY;
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors);
}

#else // _WIN32

#define COLOR(FGBG, CODE, BOLD) "\033[0;" BOLD FGBG CODE "m"

#define ALLCOLORS(FGBG,BOLD) {\
    COLOR(FGBG, "0", BOLD),\
    COLOR(FGBG, "1", BOLD),\
    COLOR(FGBG, "2", BOLD),\
    COLOR(FGBG, "3", BOLD),\
    COLOR(FGBG, "4", BOLD),\
    COLOR(FGBG, "5", BOLD),\
    COLOR(FGBG, "6", BOLD),\
    COLOR(FGBG, "7", BOLD)\
  }

static const char* colorcodes[2][2][8] = {
 { ALLCOLORS("3",""), ALLCOLORS("3","1;") },
 { ALLCOLORS("4",""), ALLCOLORS("4","1;") }
};

PosixColorEmitter::~PosixColorEmitter() {
	std::cout << "\033[0m";
}

void PosixColorEmitter::emitColor(std::ostream &os, ColorEmitter::Color c,
                                    bool background) {
	os << colorcodes[background?1:0][0][c&7];
}

#endif // POSIX
