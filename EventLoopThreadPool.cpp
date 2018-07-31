#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool(const int threadNum)
	:_threadNum(threadNum),
	_nextID(0)
{
	for (int i = 0; i < threadNum; ++i) {
		EventLoopThread *thread = new EventLoopThread();
		_threads.push_back(thread);
	}
}

EventLoopThreadPool::~EventLoopThreadPool()
{
	for (int i = 0; i < _threadNum; ++i)
		delete _threads[i];
}

//每次以轮询的方式获取一个工作线程
EventLoopThread * EventLoopThreadPool::getNextThread()
{
	if (_nextID >= _threadNum)
		_nextID = 0;
	return _threads[_nextID++];
}
