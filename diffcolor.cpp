#include "coloremitter.h"

#include <algorithm>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#else
#include <unistd.h>
#endif

void highlightTrailingWhitespace(std::string& str, ColorEmitter *c) {
	int space = str.length();
	for (std::string::reverse_iterator i = str.rbegin(), e = str.rend();
	     i != e; ++i) {
		if (*i != ' ' && *i != '\t')
			break;
		space--;
	}
	std::cout << str.substr(0, space) << c->redbg() << str.substr(space) << c->standard() << '\n';
}

int main() {
	std::auto_ptr<ColorEmitter> c(new WindowsColorEmitter());

	if (!isatty(1)) {
		std::cerr << "Error: won't write colors to a file" << std::endl;
		return 1;
	}

	for (std::string line; !std::cin.eof(); std::getline(std::cin, line)) {
		if (line.length() > 0) {
			if (line[0] == '+') {
				std::cout << c->green();
				highlightTrailingWhitespace(line, &*c);
			} else if (line[0] == '-')
				std::cout << c->red() << line << c->standard() << '\n';
			else if (line.length() > 1 && line[0] == '@' && line[1] == '@')
				std::cout << c->blue() << line << c->standard() << '\n';
			else
				std::cout << line << '\n';
		} else {
			std::cout << '\n';
		}
	}
}
