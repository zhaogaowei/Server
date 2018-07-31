#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <sstream>

//�������������ݴ洢��http_request�ṹ����
typedef struct {
	std::string method;		//����ķ���
	std::string uri;		//�����URI
	std::string version;	//HTTP�汾
	std::string host;		//�����������
	std::string connection;	//connection�ײ�
}HTTPRequest;

class Parser {
public:
	Parser(const std::string request);
	HTTPRequest getParserResult();
private:
	void parseLine();				//�������н�������_lines������
	void parseHeaders();			//����ͷ���ֶ�
	void parseRequestLine();		//����������
	std::string _request;			//�ͻ�ԭʼ����
	std::vector<std::string> _lines;
	HTTPRequest _parseResult;
};

#endif // !PARSER_H
