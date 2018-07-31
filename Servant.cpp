#include <cstdio>
#include <iostream>
#include "Socket.h"
#include "EventLoopThreadPool.h"

int main(int argc,char *argv[])
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
		return 0;
	}
	int port = atoi(argv[1]);

	
	int listenFd = Socket::createSocket();
	Socket::setReuseAddr(listenFd, true);
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	Socket::Bind(listenFd, servAddr);
	Socket::Listen(listenFd);


	EventLoopThreadPool *threadPool = new EventLoopThreadPool(4);
	while (true)
	{
		struct sockaddr_in clientAddr;
		socklen_t clientAddrLen = sizeof(clientAddr);
		memset(&clientAddr, 0, clientAddrLen);
		int connFd = Socket::Accept(listenFd, &clientAddr);

		//��ѡһ���̣߳����������׽���ע�ᵽ���̵߳�EventLoop��
		EventLoopThread *thread = threadPool->getNextThread();
		EventLoop *loop = thread->getLoop();
		loop->addToLoop(connFd);
		loop->loop();
	}
	Socket::Close(listenFd);
	delete threadPool;
	return 0;
}