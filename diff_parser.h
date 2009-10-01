//===========================================================================//
// (c) Benjamin Kramer
// This file is distributed under the MIT License. See LICENSE for details.
//===========================================================================//

#ifndef DIFFPARSER_H
#define DIFFPARSER_H

#include <vector>
#include <string>

class DiffConsumer;

class DiffParser {
	std::vector<DiffConsumer*> consumers;
public:
	void addConsumer(DiffConsumer* c) {
		consumers.push_back(c);
	}

	void handleLine(const std::string& line);
};

#endif // DIFFPARSER_H
