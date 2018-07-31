#ifndef EPOOL_H
#define EPOOL_H

#include <sys/epoll.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "Handler.h"

class EventLoop;

class Epoll {
public:
	explicit Epoll(EventLoop *loop) :ownerLoop(loop),
		epollfd(epoll_create1(EPOLL_CLOEXEC)),
		retEvents(8) // ��ʼʱΪepoll_waitԤ��8�����ص�epoll_event 
	{
		if (epollfd < 0) {
			std::cout << "Epoll::epoll_create1() error: " << ::strerror(errno) << std::endl;
			assert(epollfd > 0);
		}
	}
	~Epoll() {
		close(epollfd);
	}
	// ����epoll_wait�������佻��Event���handleEvent��������
	void epoll(std::vector<Handler*> &events);
	void removeFd(const int fd);
	void addToEpoll(const int fd);

private:
	EventLoop *ownerLoop;
	int epollfd;
	std::vector<struct epoll_event> retEvents;
};

#endif // !EPOOL_H
