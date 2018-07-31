#include "EventLoop.h"

EventLoop::EventLoop() :isLooping(false),
	threadId(CurrentThread::gettid()),
	isQuit(false),
	e(new Epoll(this)){}

EventLoop::~EventLoop()
{
	assert(!isLooping);
}

void EventLoop::loop()
{
	if (isLooping != false)
		return;
	isLooping = true;
	isQuit = false;

	while (!isQuit) {
		std::cout << "--------Looping----------" << std::endl;
		addToLoop();
		std::vector<Handler*> activeEvents;
		activeEvents.clear();
		// ����epoll������׽�����������Ӧ��Handlerȡ��������
		e->epoll(activeEvents);
		for (auto iter = activeEvents.begin(); iter != activeEvents.end(); ++iter) {
			std::cout << "---------------Handle request--------------" << std::endl;
			(*iter)->handle();
			e->removeFd((*iter)->connfd());
			delete *iter;
		}
	}
	isLooping = false;
}

void EventLoop::quit()
{
	isQuit = true;
}

// ÿ�ν�һ���׽�����������ӵ�������������
void EventLoop::addToLoop(const int fd)
{
	std::cout << "--------------Add " << fd << " to loop---------------" << std::endl;
	fds.push_back(fd);
}

// �������������е������׽���ȫ����ӵ�epoll��
void EventLoop::addToLoop()
{
	if (fds.empty()) {
		std::cout << "-------fds empty---------- " << std::endl;
		return;
	}
	for (int i = 0; i < fds.size(); ++i) {
		e->addToEpoll(fds[i]);
	}
	fds.clear();
	std::cout << "--------Add all fd to loop--------" << std::endl;
	
}
