#include "diff_parser.h"
#include "diff_consumer.h"

void DiffParser::handleLine(const std::string& line) {
	std::string::size_type len = line.length();
	if (len >= 1 && line[0] == '+') {
		for (std::vector<DiffConsumer*>::const_iterator i = consumers.begin(),
		     e = consumers.end(); i != e; ++i) {
			(*i)->onAdd(line);
		}
	} else if (len >=1 && line[0] == '-') {
		for (std::vector<DiffConsumer*>::const_iterator i = consumers.begin(),
		     e = consumers.end(); i != e; ++i) {
			(*i)->onDelete(line);
		}
	} else if (len >= 2 && line[0] == '@' && line[1] == '@') {
		for (std::vector<DiffConsumer*>::const_iterator i = consumers.begin(),
		     e = consumers.end(); i != e; ++i) {
			(*i)->onHunk(line);
		}
	} else {
		for (std::vector<DiffConsumer*>::const_iterator i = consumers.begin(),
		     e = consumers.end(); i != e; ++i) {
			(*i)->onLine(line);
		}
	}
}
