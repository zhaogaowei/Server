#include "Parser.h"

Parser::Parser(const std::string request) {
	assert(request.length() > 0);
	this->_request = request;
}

HTTPRequest Parser::getParserResult() {
	parseLine();
	parseRequestLine();
	parseHeaders();
	return _parseResult;
}


void Parser::parseLine() {
	std::istringstream in(_request);
	std::string str;
	while (getline(in,str))
	{
		_lines.push_back(str);
	}
	return;
}

void Parser::parseRequestLine() {
	assert(_lines.size() > 0);
	std::istringstream ss(_lines[0]);

	ss >> _parseResult.method;
	if (_parseResult.method.empty()) {
		std::cout << "Request1 error." << std::endl;
		return;
	}

	ss >> _parseResult.uri;
	if (_parseResult.uri.empty()) {
		std::cout << "Request2 error." << std::endl;
		return;
	}

	ss >> _parseResult.version;
	if (_parseResult.version.empty()) {
		std::cout << "Request3 error." << std::endl;
		return;
	}
}

void Parser::parseHeaders() {
	assert(_lines.size() > 0);
	for (int i = 1; i < _lines.size(); ++i) {
		std::istringstream ss(_lines[i]);
		std::string temp;
		if (_lines[i].empty())
			continue;
		else if (ss>>temp) {
			if (temp == "Host:") {
				ss >> temp;
				_parseResult.host = temp;
			}
			else if (temp == "Connection:") {
				ss >> temp;
				_parseResult.connection = temp;
			}
			else {

			}
		}
	}
}