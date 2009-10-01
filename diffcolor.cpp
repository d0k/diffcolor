#include "color_emitter.h"
#include "diff_consumer.h"
#include "diff_parser.h"

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
#ifdef _WIN32
	std::auto_ptr<ColorEmitter> c(new WindowsColorEmitter());
#else
	std::auto_ptr<ColorEmitter> c(new PosixColorEmitter());
#endif

	if (!isatty(1)) {
		std::cerr << "Error: won't write colors to a file" << std::endl;
		return 1;
	}

	DiffParser dp;
	std::auto_ptr<DiffConsumer> cc(new ColorConsumer(std::cout, &*c, true));
	dp.addConsumer(&*cc);

	for (std::string line; !std::cin.eof(); std::getline(std::cin, line)) {
		dp.handleLine(line);
	}
}
