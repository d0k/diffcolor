//===========================================================================//
// (c) Benjamin Kramer
// This file is distributed under the MIT License. See LICENSE for details.
//===========================================================================//

#ifndef DIFFCONSUMER_H
#define DIFFCONSUMER_H

#include <iosfwd>
#include <string>

class DiffConsumer {
public:
	virtual void onHunk(const std::string&) {}
	virtual void onFile(const std::string&) {}
	virtual void onAdd(const std::string&) {}
	virtual void onDelete(const std::string&) {}
	virtual void onLine(const std::string&) {}
};

class ColorEmitter;

class ColorConsumer : public DiffConsumer {
	std::ostream* os;
	ColorEmitter *c;
	bool highlightWhitespace;
protected:
	std::string::size_type getTrailingWhitespaceAmount(const std::string& str);
	void highlightTrailingWhitespace(const std::string& str);
public:
	ColorConsumer(std::ostream& os, ColorEmitter* c,
	              bool highlightWhitespace = false) : os(&os), c(c),
	              highlightWhitespace(highlightWhitespace) {}

	virtual void onHunk(const std::string& line);
	virtual void onAdd(const std::string& line);
	virtual void onDelete(const std::string& line);
	virtual void onLine(const std::string& line);
};

#endif // DIFFCONSUMER_H
