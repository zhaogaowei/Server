#include "Epoll.h"

void Epoll::epoll(std::vector<Handler*>& activeEvents)
{
	int numEvents = epoll_wait(epollfd, retEvents.data(), static_cast<int>(retEvents.size()), 1000);
	if (numEvents < 0) {
		if (errno != EINTR) {// FIXME: 调用日志库写入日志并终止程序
			std::cout << "Epoll::epoll() error: " << strerror(errno) << std::endl;
			exit(1);
		}
	}
	else {
		for (int i = 0; i < numEvents; i++) {
			Handler *h = new Handler(retEvents[i].data.fd);
			activeEvents.push_back(h);
		}
	}
}

void Epoll::removeFd(const int fd)
{
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}

void Epoll::addToEpoll(const int fd)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLPRI | EPOLLRDHUP;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event) < 0)
		std::cout << "Epoll::addToEpoll error: " << strerror(errno) << std::endl;
	std::cout << "--------------Add to Epoll--------------" << std::endl;
}
