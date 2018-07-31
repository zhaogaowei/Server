#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Parser.h"
#include "Buffer.h"

class Handler {
public:
	Handler(const int connfd);
	~Handler();
	void handle();
	const int connfd() const { return _connfd; }
private:
	bool receiveRequest();		//接收客户端请求并解析
	//void sendResponse();		//发送响应
	void sendErrorMsg(const std::string &errorNum,
		const std::string &shortMsg,
		const std::string &longMsg);
	void parserURI();
	void getFileType();
	int _connfd;
	bool _isClosed;
	std::string _fileType;
	std::string _fileName;
	Buffer _inputBuffer;
	Buffer _outputBuffer;
	HTTPRequest _request;
};

#endif // !HANDLER_H

