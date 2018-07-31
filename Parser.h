#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <sstream>

//解析请求后的数据存储在http_request结构体中
typedef struct {
	std::string method;		//请求的方法
	std::string uri;		//请求的URI
	std::string version;	//HTTP版本
	std::string host;		//请求的主机名
	std::string connection;	//connection首部
}HTTPRequest;

class Parser {
public:
	Parser(const std::string request);
	HTTPRequest getParserResult();
private:
	void parseLine();				//将请求按行解析存入_lines数组中
	void parseHeaders();			//解析头部字段
	void parseRequestLine();		//解析请求行
	std::string _request;			//客户原始请求
	std::vector<std::string> _lines;
	HTTPRequest _parseResult;
};

#endif // !PARSER_H
