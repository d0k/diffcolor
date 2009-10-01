#include "diff_consumer.h"
#include "color_emitter.h"

#include <iostream>

std::string::size_type ColorConsumer::getTrailingWhitespaceAmount(
                       const std::string& str) {
	if (str.length() <= 1)
		return 0;
	std::string::size_type space = str.length();
	for (std::string::size_type i = space-1; i >= 1; --i) {
		if (str[i] != ' ' && str[i] != '\t')
			break;
		space--;
	}
	return space;
}

void ColorConsumer::highlightTrailingWhitespace(const std::string& str) {
	if (!highlightWhitespace || str.length() <= 1) {
		*os << str << c->standard() << '\n';
		return;
	}
	std::string::size_type space = getTrailingWhitespaceAmount(str);
	*os << str.substr(0, space) << c->redbg() << str.substr(space)
	    << c->standard() << '\n';
}

void ColorConsumer::onHunk(const std::string& line) {
	*os << c->blue() << line << c->standard() << '\n';
}

void ColorConsumer::onAdd(const std::string& line) {
	*os << c->green();
	highlightTrailingWhitespace(line);
}

void ColorConsumer::onDelete(const std::string& line) {
	*os << c->red();
	highlightTrailingWhitespace(line);
}

void ColorConsumer::onLine(const std::string& line) {
	highlightTrailingWhitespace(line);
}
